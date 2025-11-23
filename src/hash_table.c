#include "hash_table.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "astring.h"
#include "hash.h"

#define INITIAL_CAPACITY 16

typedef struct {
    const char* key;
    void* value;
} hash_table_entry;

struct a_hash_table_t {
    hash_table_entry* entries;
    size_t cap;
    size_t len;
};

a_hash_table_t* a_hash_table_create() {
    a_hash_table_t* t = malloc(sizeof(a_hash_table_t));
    if (t == NULL) {
        return NULL;
    }
    t->cap = INITIAL_CAPACITY;
    t->len = 0;

    t->entries = calloc(t->cap, sizeof(hash_table_entry));
    if (t->entries == NULL) {
        free(t);
        return NULL;
    }

    return t;
}

void a_hash_table_free(a_hash_table_t* t) {
    if (t == NULL) {
        return;
    }

    for (size_t i = 0; i < t->cap; i++) {
        free((void*)t->entries[i].key);
    }

    free(t->entries);
    free(t);
}

void* a_hash_table_get(a_hash_table_t* t, const char* k) {
    uint64_t h = a_hash_fnv1a_64(k, sizeof(uint64_t));
    size_t i = h % t->cap;

    if (t->entries[i].key == NULL) {
        return NULL;
    }

    size_t c = 0;
    while (c < (t->cap)) {
        // TODO bug?
        if (t->entries[i].key == NULL) {
            return NULL;
        }

        if (strcmp(t->entries[i].key, k) == 0) {
            return t->entries[i].value;
        }

        if (i < (t->cap - 1)) {
            i++;
        } else {
            i = 0;
        }

        c++;
    }

    return NULL;
}

void* a_hash_table_set(a_hash_table_t* t, const char* k, void* v) {
    if (t->len > (t->cap / 2)) {
        hash_table_entry* nentries =
            calloc(t->cap * 2, sizeof(hash_table_entry));
        if (nentries == NULL) {
            return NULL;  // TODO
        }

        for (size_t i = 0; i < t->cap; i++) {
            if (t->entries[i].key == NULL) {
                continue;
            }

            uint64_t h = a_hash_fnv1a_64(k, sizeof(uint64_t));
            size_t j = h % (t->cap * 2);

            if (nentries[j].key == NULL) {
                nentries[j].key = t->entries[i].key;
                nentries[j].value = t->entries[i].value;
            } else {
                size_t c = 0;
                while (c < (t->cap * 2)) {
                    if (nentries[j].key == NULL) {
                        nentries[j].key = t->entries[i].key;
                        nentries[j].value = t->entries[i].value;
                        break;
                    }

                    if (j < ((t->cap * 2) - 1)) {
                        j++;
                    } else {
                        j = 0;
                    }

                    c++;
                }
            }
        }

        free(t->entries);
        t->cap = t->cap * 2;
        t->entries = nentries;
    }

    uint64_t h = a_hash_fnv1a_64(k, sizeof(uint64_t));
    size_t i = h % t->cap;

    if (t->entries[i].key == NULL) {
        char* key = a_strdup(k);
        if (key == NULL) {
            return NULL;
        }

        t->len += 1;
        t->entries[i].key = (const char*)key;
        t->entries[i].value = v;
    } else {
        size_t c = 0;
        while (c < (t->cap)) {
            if (t->entries[i].key == NULL) {
                char* key = a_strdup(k);
                if (key == NULL) {
                    return NULL;
                }

                t->len += 1;
                t->entries[i].key = (const char*)key;
                t->entries[i].value = v;
                return t->entries[i].value;
            }

            if (strcmp(t->entries[i].key, k) == 0) {
                t->entries[i].value = v;
                return t->entries[i].value;
            }

            if (i < (t->cap - 1)) {
                i++;
            } else {
                i = 0;
            }

            c++;
        }

        return NULL;
    }

    return t->entries[i].value;
}

size_t a_hash_table_len(a_hash_table_t* t) { return t->len; }

void a_hash_table_dump(a_hash_table_t* t) {
    printf("index     \tkey       \tvalue\n");
    for (size_t i = 0; i < t->cap; i++) {
        const char* k = t->entries[i].key;
        void* v = t->entries[i].value;
        printf("%14ld\t%14p\t%14p\n", i, k, v);
    }
}
