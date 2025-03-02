#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stddef.h>

/**
 * @brief Hash Function that follows the FNV algorithm
 * 
 * @param key Key
 * @return hash value 
 */
size_t fnv_hash(const char *key);

/**
 * @brief Hash Function that simply adds the value of the character
 * 
 * @param key Key
 * @return hash value 
 */
size_t character_folding(const char *key);

/**
 * @brief Hash Function
 * 
 * @param key Key
 * @return hash value 
 */
size_t djb2(const char *key);

/**
 * @brief Hash Function
 * 
 * @param key Key
 * @return hash value 
 */
size_t sdbm(const char *str);

#endif