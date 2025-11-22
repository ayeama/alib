#ifndef A_HASH_H
#define A_HASH_H

#include <stdint.h>

uint64_t a_hash_fnv1a_64(const void *key, const uint64_t len);

#endif  // A_HASH_H
