#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stddef.h>

size_t fnv_hash(const char *key);
size_t character_folding(const char *key);

#endif