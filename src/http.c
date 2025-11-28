#include "http.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "astring.h"

#define RADIX_EDGE_LIST_CAP 4

typedef struct radix_edge_list_item radix_edge_list_item;
typedef struct radix_edge_list radix_edge_list;
typedef struct radix_node radix_node;
radix_node *radix_create();
void radix_free(radix_node *root);
void radix_insert(radix_node *root, const char *text, void *value);
void *radix_search(radix_node *root, const char *text);

typedef struct radix_edge_list_item {
    char *label;
    radix_node *node;
} radix_edge_list_item;

typedef struct radix_edge_list {
    radix_edge_list_item *items;
    size_t len;
    size_t cap;
} radix_edge_list;

static radix_edge_list_item *radix_edge_list_get(radix_edge_list *list,
                                                 char first) {
    for (size_t i = 0; i < list->len; i++) {
        if (list->items[i].label[0] == first) {
            return &list->items[i];
        }
    }
    return NULL;
}

static bool radix_edge_list_add(radix_edge_list *list, const char *label,
                                void *node) {
    if (list->len == list->cap) {
        size_t ncap = list->cap ? list->cap * 2 : RADIX_EDGE_LIST_CAP;
        radix_edge_list_item *nitems =
            realloc(list->items, (sizeof *nitems) * ncap);
        if (nitems == NULL) {
            return false;
        }
        list->items = nitems;
        list->cap = ncap;
    }

    list->items[list->len].label = a_strdup(label);
    list->items[list->len].node = node;
    list->len++;
    return true;
}

static void radix_edge_list_free(radix_edge_list *list) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->len; i++) {
        free(list->items[i].label);
    }

    free(list->items);
    list->items = NULL;
    list->len = 0;
    list->cap = 0;
}

typedef struct radix_node {
    radix_edge_list edges;
    bool terminal;
    void *value;
} radix_node;

radix_node *radix_create() {
    radix_node *root = calloc(1, sizeof *root);
    if (root == NULL) {
        // TODO
        return NULL;
    }

    return root;
}

void radix_free(radix_node *root) {
    if (root == NULL) {
        return;
    }

    for (size_t i = 0; i < root->edges.len; i++) {
        radix_node *child = root->edges.items[i].node;
        radix_free(child);
        free(root->edges.items[i].label);
    }

    free(root->edges.items);
    free(root);
}

void radix_insert(radix_node *root, const char *text, void *value) {
    radix_node *cur = root;
    const char *key = text;

    while (*key) {
        radix_edge_list_item *edge = radix_edge_list_get(&cur->edges, *key);
        if (edge == NULL) {
            radix_node *nnode = calloc(1, sizeof *nnode);
            if (nnode == NULL) {
                return;
            }
            nnode->terminal = true;
            nnode->value = value;
            if (!radix_edge_list_add(&cur->edges, key, nnode)) {
                return;
            }
            return;
        }

        char *label = edge->label;
        size_t i = 0;

        while (key[i] && label[i] && key[i] == label[i]) {
            i++;
        }

        if (i == strlen(label)) {
            cur = edge->node;
            key += i;
            continue;
        }

        radix_node *snode = calloc(1, sizeof *snode);
        if (snode == NULL) {
            return;
        }

        radix_node *ochild = edge->node;
        radix_edge_list_add(&snode->edges, label + i, ochild);

        radix_node *nnode = calloc(1, sizeof *nnode);
        nnode->terminal = true;
        radix_edge_list_add(&snode->edges, key + i, nnode);

        free(edge->label);
        edge->label = a_strndup(label, i);
        edge->node = snode;
        return;
    }

    cur->terminal = true;
}

void *radix_search(radix_node *root, const char *text) {
    radix_node *cur = root;
    const char *key = text;

    while (*key) {
        radix_edge_list_item *edge = radix_edge_list_get(&cur->edges, *key);
        if (edge == NULL) {
            return false;
        }

        char *label = edge->label;
        size_t i = 0;

        while (key[i] && label[i] && key[i] == label[i]) {
            i++;
        }

        if (i < strlen(label)) {
            return false;
        }

        key += i;
        cur = edge->node;
    }

    return cur->value;
}

void _handle_connection(a_http_server_t *server, int socket) {
    printf("_handle_connection\n");
    a_http_request_t r = {};

    void *result =
        radix_search((radix_node *)server->handler->funcs, "GET /users");
    a_http_handler_func_t func = (a_http_handler_func_t)result;
    func(&r);
}

void a_http_handle_func(a_http_handler_t *handler, const char *pattern,
                        a_http_handler_func_t func) {
    if (handler->funcs == NULL) {
        handler->funcs = radix_create();  // TODO handle free
    }
    radix_insert(handler->funcs, pattern, func);
}

void a_http_serve(a_http_server_t *server) {
    int serverfd;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
    }

    int opt = 1;
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) !=
        0) {
        perror("setsockopt failed");
        // TODO logging
    }

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(server->host),
        .sin_port = htons(server->port),
    };

    if (bind(serverfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        // TODO logging
    }

    if (listen(serverfd, 3) < 0) {
        perror("listen failed");
        // TODO logging
    }

    while (true) {
        int socket;
        socklen_t addrlen = sizeof(address);
        if ((socket = accept(serverfd, (struct sockaddr *)&address, &addrlen)) <
            0) {
            perror("accept failed");
            // TODO logging
        }

        _handle_connection(server, socket);
        close(socket);
    }

    close(serverfd);
}
