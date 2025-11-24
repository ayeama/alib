#ifndef A_TRIE_H
#define A_TRIE_H

#include <stdbool.h>

#define TRIE_CHARSET_COUNT 256

typedef struct a_trie_node_t {
    struct a_trie_node_t *children[TRIE_CHARSET_COUNT];
    bool terminal;
} a_trie_node_t;

a_trie_node_t *a_trie_create();

void a_trie_free(a_trie_node_t *root);

bool a_trie_insert(a_trie_node_t **root, char *text);

bool a_trie_search(a_trie_node_t *root, char *text);

void a_trie_delete();

void a_trie_dump(a_trie_node_t *root);

#endif  // A_TRIE_H
