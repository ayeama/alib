#ifndef A_HASH_TABLE_H
#define A_HASH_TABLE_H

#include <stdlib.h>

typedef struct a_hash_table_t a_hash_table_t;

a_hash_table_t* a_hash_table_create();

void a_hash_table_free(a_hash_table_t* ht);

void* a_hash_table_get(a_hash_table_t* ht, const char* key);

void* a_hash_table_set(a_hash_table_t* ht, const char* key, void* value);

size_t a_hash_table_length(a_hash_table_t* ht);

#endif  // A_HASH_TABLE_H
