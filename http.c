#include <alib/http.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void _handle_connection(a_http_server_t *server, int socket) {
    printf("_handle_connection\n");
    chttp_request_t r = {};
    server->handler->func(&r);
}

void a_http_handle_func(a_http_handler_t *handler, const char *pattern,
                        void (*func)(chttp_request_t *r)) {
    printf("a_http_handle_func\n");
    handler->func = func;
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
        // TODO
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
