#include "hash_table.h"
#include "hash_functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INIT_SIZE 17

#define FREE 0
#define DELETED 1
#define USED 2

#define GROW 1
#define SHRINK (-1)
#define CLEAN 0

struct bucket {
    char *key;
    void *data;
    unsigned char status;
};

typedef struct hash_table {
    size_t size, count;
    size_t (*hash)(const char *);
    struct bucket *table;
} Hash_Table;

Hash_Table *ht_create(size_t size, size_t (*hash)(const char *)) {
    if (hash == NULL)
        return NULL;

    Hash_Table * new = (Hash_Table *)malloc(sizeof(Hash_Table));
    if (new == NULL)
        return NULL;

    if (size == 0)
        size = INIT_SIZE;

    new->table = (struct bucket *)malloc(size * sizeof(struct bucket));
    if (new->table == NULL) {
        free(new);
        return NULL;
    }

    new->size = size;
    new->count = 0;
    new->hash = hash;

    for (size_t i = 0; i < size; i++)
        new->entries[i].status = FREE;

    return new;
}

void ht_destroy(Hash_Table *ht, void (*destroy)(void *)) {
    if (ht == NULL || destroy == NULL)
        return;

    if (ht->table != NULL) {
        for (size_t i = 0; i < ht->size; i++) {
            if (ht->table[i].data != NULL)
                destroy(ht->table[i].data);

            if (ht->table[i].key != NULL)
                free(ht->table[i].key);
        }

        free(ht->table);
    }

    free(ht);
}

/**
 * @brief Determines if <u>key<u> exists in the table, returning it's index.
 * If it does not exist returns the index in which it should be.
 * 
 * @param ht Hash Table
 * @param key Key
 * @return Index to where it is or it should be
 */
static size_t ht_where(const Hash_Table *ht, const char *key) {
    size_t index = ht->hash(key) % ht->size;
    size_t count = 0;
    size_t result = ht->size;

    for (count = 0; count < ht->size && ht->table[index].status == USED && strcmp(ht->table[index].key, key) != 0; count++)
        index = (index + 1) % ht->size;

    if (count < ht->size) {
        result = index;

        if (ht->table[index].status != USED) {
            for (; count < ht->size && ht->table[index].status != FREE; count++)
                index = (index + 1) % ht->size;



        }
    }

    return result;
}

/**
 * @brief Calculates the load factor of a Hash Table
 * 
 * Assumes <u>ht<u> is not NULL
 * 
 * @param ht Hash Table
 * @return Load Factor
 */
static float ht_load_factor(const Hash_Table *ht) {
    return (float) ht->count / (float) ht->size;
}

/**
 * @brief Resizes the hash table according to <u>change<u>.
 * 
 * If change > 0, doubles the size, < 0, reduces to 2/3, == 0, cleans the table
 * 
 * Assumes <u>ht<u> is not NULL
 * 
 * @param ht Hash Table
 * @param change Change Factor
 * @return 0 on sucess, 1 allocation failure
 */
static int ht_rehash(Hash_Table *ht, int change) {



}

int ht_insert(Hash_Table *ht, void *data, const char *key) {
    if (ht == NULL || key == NULL)
        return 1;

    if (ht_load_factor(ht) == 0.8)
        if (ht_rehash(ht, GROW) != 0)
            return 2;

    size_t index = ht_where(ht, key);

    if (ht->table[index].status != USED) {
        ht->table[index].status = USED;
        ht->table[index].data = data;
        ht->table[index].key = strdup(key);

        ht->count++;
    }

    return 0;
}

void *ht_remove(Hash_Table *ht, const char *key) {
    void *result = NULL;
    if (ht != NULL && key != NULL) {
        size_t index = ht_where(ht, key);

        // key exists in the table
        if (ht->table[index].status == USED) {
            ht->table[index].status = DELETED;
            result = ht->table[index].data;

            ht->count--;
        }
    }
    return result;
}

void *ht_lookup(const Hash_Table *ht, const char *key) {
    void *result = NULL;
    if (ht != NULL && key != NULL) {
        size_t index = ht_where(ht, key);

        if (ht->table[index].status == USED)
            result = ht->table[index].data;
    }

    return result;
}

bool ht_check(const Hash_Table *ht, const char *key) {
    bool result = NULL;
    if (ht != NULL && key != NULL) {
        size_t index = ht_where(ht, key);

        if (ht->table[index].status == USED)
            result = true;
    }

    return result;
}

size_t ht_elements(const Hash_Table *ht) {
    if (ht != NULL)
        return ht->count;
    return 0;
}

void ht_show(const Hash_Table *ht, void (*show)(const void *, const char *, FILE *), FILE *fp) {
    if (ht == NULL || show == NULL || fp == NULL || ht->table == NULL)
        return NULL;

    for (size_t i = 0; i < ht->size; i++) {
        switch (ht->table[i].status ) {
            case USED:
                show(ht->table[i].data, ht->table[i].key, fp);
                break;
            case DELETED:
                fprintf(fp, "%ld is DELETED\n");
                break;
            case FREE:
                fprintf(fp, "%ld is FREE\n");
                break;
            default:
                break;
        }
    }
}
