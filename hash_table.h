#ifndef A_HASH_TABLE_H
#define A_HASH_TABLE_H

#include <stdlib.h>

typedef struct a_hash_table_t a_hash_table_t;

a_hash_table_t* a_hash_table_create();

void a_hash_table_free(a_hash_table_t* t);

void* a_hash_table_get(a_hash_table_t* t, const char* k);

void* a_hash_table_set(a_hash_table_t* t, const char* k, void* v);

size_t a_hash_table_len(a_hash_table_t* t);

// TODO for debugging
void a_hash_table_dump(a_hash_table_t* t);

#endif  // A_HASH_TABLE_H
