#ifndef A_HTTP_H
#define A_HTTP_H

typedef struct {
    const char *method;
    const char *request_uri;
    const char *http_version;
} a_http_request_t;

typedef struct {
} a_http_response_t;

typedef void (*a_http_handler_func_t)(a_http_request_t *r);

typedef struct {
    // TODO use a hash table/decision tree
    // void (*func)(a_http_request_t *r);
    void *funcs; // void* = radix_node*
} a_http_handler_t;

void a_http_handle_func(a_http_handler_t *handler, const char *pattern,
                        a_http_handler_func_t func);

typedef struct {
    // TODO merge host and port into address
    const char *host;
    int port;
    a_http_handler_t *handler;
} a_http_server_t;

void a_http_serve(a_http_server_t *server);

#endif  // A_HTTP_H
