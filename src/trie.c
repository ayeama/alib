#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

a_trie_node_t *a_trie_create() {
    a_trie_node_t *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }

    for (int i = 0; i < TRIE_CHARSET_COUNT; i++) {
        node->children[i] = NULL;
    }
    node->terminal = false;

    return node;
}

void a_trie_free(a_trie_node_t *root) {
    if (root == NULL) {
        return;
    }
    // TODO not implemented
}

bool a_trie_insert(a_trie_node_t **root, char *text) {
    if (*root == NULL) {
        *root = a_trie_create();
    }

    a_trie_node_t *tmp = *root;
    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (tmp->children[text[i]] == NULL) {
            tmp->children[text[i]] = a_trie_create();
        }
        tmp = tmp->children[text[i]];
    }

    if (!tmp->terminal) {
        tmp->terminal = true;
    }
    return tmp->terminal;
}

bool a_trie_search(a_trie_node_t *root, char *text) {
    int len = strlen(text);
    a_trie_node_t *tmp = root;

    for (int i = 0; i < len; i++) {
        if (tmp->children[text[i]] == NULL) {
            return false;
        }
        tmp = tmp->children[text[i]];
    }
    return tmp->terminal;
}

void a_trie_delete() {
    // TODO not implemented
}

void trie_dump_r(a_trie_node_t *node, char *prefix, int len) {
    if (node->terminal) {
        printf("%s\n", prefix);
    }

    char newprefix[len + 2];
    memcpy(newprefix, prefix, len);
    newprefix[len + 1] = 0;

    for (int i = 0; i < TRIE_CHARSET_COUNT; i++) {
        if (node->children[i] != NULL) {
            newprefix[len] = i;
            trie_dump_r(node->children[i], newprefix, len + 1);
        }
    }
}

void a_trie_dump(a_trie_node_t *root) {
    printf("trie dump\n");

    if (root == NULL) {
        return;
    }
    trie_dump_r(root, NULL, 0);
}
