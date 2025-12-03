#ifndef A_HASH_TABLE_H
#define A_HASH_TABLE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct a_hash_table_t a_hash_table_t;

a_hash_table_t* a_hash_table_create();

void a_hash_table_free(a_hash_table_t* t);

void* a_hash_table_get(a_hash_table_t* t, const char* k);

void* a_hash_table_set(a_hash_table_t* t, const char* k, void* v);

size_t a_hash_table_len(a_hash_table_t* t);

// TODO for debugging
void a_hash_table_dump(a_hash_table_t* t);

typedef struct a_hash_table_iter_t {
    const char* key;
    void* value;
    a_hash_table_t* _t;
    size_t _index;
} a_hash_table_iter_t;

a_hash_table_iter_t a_hash_table_iter(a_hash_table_t* t);

bool a_hash_table_iter_next(a_hash_table_iter_t* i);

#endif  // A_HASH_TABLE_H
