#include "array.h"

#include <stdio.h>

#define A_ARRAY_INITIAL_CAPACITY 8

void resize(a_parray_t *a) {
    if (a->len >= (a->cap / 2)) {
        printf("parray resize\n");
        size_t ncap = a->cap * 2;
        void **nitems = realloc(a->items, sizeof(void *) * ncap);
        if (nitems == NULL) {
            return;
        }
        a->items = nitems;
        a->cap = ncap;
    }
}

a_parray_t *a_parray_create() {
    a_parray_t *a = malloc(sizeof *a);
    if (a == NULL) {
        return NULL;
    }

    a->items = calloc(A_ARRAY_INITIAL_CAPACITY, sizeof(void *));
    if (a->items == NULL) {
        free(a);
        return NULL;
    }

    a->cap = A_ARRAY_INITIAL_CAPACITY;
    a->len = 0;

    return a;
}

void a_parray_free(a_parray_t *a) {
    if (a == NULL) {
        return;
    }
    free(a);
}

void a_parray_add(a_parray_t *a, void *d) {
    if (a == NULL) {
        return;
    }
    resize(a);

    a->items[a->len] = d;
    a->len++;
}

void a_parray_dump(a_parray_t *a) {
    printf("pointer array dump\n");
    printf("capacity %d\nlength %d\n", a->cap, a->len);
    printf("[");
    for (int i = 0; i < a->len; i++) {
        printf("%p", a->items[i]);
        if (i != (a->len - 1)) {
            printf(", ");
        }
    }
    printf("]\n");
}
