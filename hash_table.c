#include <alib/hash_table.h>

#define INITIAL_CAPACITY 16

typedef struct {
    const char *key;
    void *value;
} hash_table_entry;

struct a_hash_table_t {
    hash_table_entry *entries;
    size_t capacity;
    size_t length;
};

a_hash_table_t *a_hash_table_create() {
    a_hash_table_t *ht = malloc(sizeof(a_hash_table_t));
    if (ht == NULL) {
        return NULL;
    }
    ht->capacity = INITIAL_CAPACITY;
    ht->length = 0;

    ht->entries = calloc(ht->capacity, sizeof(hash_table_entry));
    if (ht->entries == NULL) {
        free(ht);
        return NULL;
    }

    return ht;
}

void a_hash_table_free(a_hash_table_t *ht) {
    for (size_t i = 0; i < ht->capacity; i++) {
        free((void *)ht->entries[i].key);
    }

    free(ht->entries);
    free(ht);
}