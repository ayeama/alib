#include <alib/hash.h>
#include <alib/hash_table.h>
#include <alib/astring.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
  for (size_t i = 0; i < t->cap; i++) {
    free((void*)t->entries[i].key);
  }

  free(t->entries);
  free(t);
}

void* a_hash_table_get(a_hash_table_t* t, const char* k) {
  uint64_t h = a_hash_fnv1a_64(k, sizeof(uint64_t));
  size_t i = h % t->cap;

  if (strcmp(t->entries[i].key, k) == 0) {
    return t->entries[i].value;
  }
  return NULL;  // TODO
}

void* a_hash_table_set(a_hash_table_t* t, const char* k, void* v) {
  // TODO check cap
  if (t->cap < ((t->len) / 2)) {
    printf("extend hash table\n");
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
    if (strcmp(t->entries[i].key, k) == 0) {
      t->entries[i].value = v;
    } else {
      // TODO handle collisions
      printf("hash table collision\n");
    }
  }
  return t->entries[i].value;
}

size_t a_hash_table_len(a_hash_table_t* t) { return t->len; }

void a_hash_table_dump(a_hash_table_t* t) {
  printf("index     \tkey       \tvalue\n");
  for (size_t i = 0; i < t->cap; i++) {
    const char* k = t->entries[i].key;
    void* v = t->entries[i].value;
    printf("%10ld\t%010p\t%010p\n", i, k, v);
  }
}
