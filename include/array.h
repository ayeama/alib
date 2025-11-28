#ifndef A_ARRAY_H
#define A_ARRAY_H

#include <stdlib.h>

// TODO create dynamic pointer and byte arrays
typedef struct a_parray_t {
    void **items;
    size_t cap;
    size_t len;
} a_parray_t;

a_parray_t *a_parray_create();

void a_parray_free(a_parray_t *a);

void a_parray_add(a_parray_t *a, void *d);

void a_parray_dump(a_parray_t *a);

#endif  // A_ARRAY_H
