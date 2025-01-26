#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stdio.h>

/**
 * When the capacity of the table reaches 80%, it doubles it's size, reahashing every node to a new position.
 * Same thing happens when the capacity is less than 30%, only this time the size is reduced to 2/3 of the
 * original.
 */

/**
 * @brief Hash Table
 */
typedef struct hash_table Hash_Table;

Hash_Table *ht_create(size_t size, size_t (*hash)(const char *));
void ht_destroy(Hash_Table *ht, void (*destroy)(void *));

int ht_insert(Hash_Table *ht, void *data, const char *key);
void *ht_remove(Hash_Table *ht, const char *key);
void *ht_lookup(const Hash_Table *ht, const char *key);
bool ht_check(const Hash_Table *ht, const char *key);

size_t ht_elements(const Hash_Table *ht);

void ht_show(const Hash_Table *ht, void (*show)(const void *, const char *, FILE *), FILE *fp);

size_t ht_max_probe(const Hash_Table *ht);

#endif