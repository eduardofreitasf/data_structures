#include "hash_functions.h"
#include <string.h>

#define FNV_PRIME 0x01000193
#define FNV_OFFSET 0x811c9dc5

size_t fnv_hash(const char *key) {
    if (key == NULL)
        return 0;

    size_t hash = FNV_OFFSET;
    for (size_t i = 0; key[i] != '\0'; i++) {
        hash = hash ^ key[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

size_t character_folding(const char *key) {
    if (key == NULL)
        return 0;

    size_t hash = 0;
    for (size_t i = 0; key[i] != '\0'; i++)
        hash += key[i];

    return hash;
}

size_t djb2(const char *key) {
    if (key == NULL)
        return 0;

    size_t hash = 5381;
    int c;

    while (c = *key++) {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

size_t sdbm(const char *str) {
    size_t hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}
