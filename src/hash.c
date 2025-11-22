#include "hash.h"

#define FNV_PRIME_64 0x00000100000001b3
#define FNV_OFFSET_BASIS_64 0xcbf29ce484222325

// https://en.wikipedia.org/w/index.php?title=Fowler%E2%80%93Noll%E2%80%93Vo_hash_function&oldid=1312413750#FNV-1a_hash
uint64_t a_hash_fnv1a_64(const void *key, const uint64_t len) {
    const char *data = (char *)key;
    uint64_t hash = FNV_OFFSET_BASIS_64;

    for (uint64_t i = 0; i < len; i++) {
        uint8_t value = data[i];
        hash = hash ^ value;
        hash *= FNV_PRIME_64;
    }

    return hash;
}
