#ifndef A_HTTP_H
#define A_HTTP_H

#include <alib/hash_table.h>

typedef struct {
  const char *method;
  const char *request_uri;
  const char *http_version;
} chttp_request_t;

typedef struct {
} chttp_response_t;

typedef struct {
  // TODO use a hash table/decision tree
  // void (*func)(chttp_request_t *r);
  a_hash_table_t *funcs;
} a_http_handler_t;

void a_http_handle_func(a_http_handler_t *handler, const char *pattern,
                        void (*func)(chttp_request_t *r));

typedef struct {
  // TODO merge host and port into address
  const char *host;
  int port;
  a_http_handler_t *handler;
} a_http_server_t;

void a_http_serve(a_http_server_t *server);

#endif  // A_HTTP_H
