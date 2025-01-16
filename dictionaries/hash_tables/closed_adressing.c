#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

// prime number
#define DEFAULT_SIZE 17

#define GROW 1
#define SHRINK (-1)
#define CLEAN 0

/**
 * @brief Node containing the key value pair, and a pointer to another bucket
 * 
 */
struct bucket {
    void *data;
    char *key;
    struct bucket *next;
};

typedef struct hash_table {
    size_t size, count;
    struct bucket **entries;
    size_t (*hash)(const char *);
} Hash_Table;

/**
 * @brief Creates a bucket node for a Hash Table
 * 
 * Assumes key is not NULL
 * 
 * @param data Data to store
 * @param key Key to identify data
 * @return NULL allocation failure
 * @return struct bucket * Allocated bucket
 */
static struct bucket *create_bucket(void *data, const char *key) {
    struct bucket *new = (struct bucket *)malloc(sizeof(struct bucket));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->key = strdup(key);
    new->next = NULL;

    return new;
}

Hash_Table *ht_create(size_t size, size_t (*hash)(const char *)) {
    if (hash == NULL)
        return NULL;

    Hash_Table * new = (Hash_Table *)malloc(sizeof(Hash_Table));
    if (new == NULL)
        return NULL;

    if (size == 0)
        size = DEFAULT_SIZE;

    new->entries = (struct bucket **)malloc(size * sizeof(struct bucket *));
    if (new->entries == NULL) {
        free(new);
        return NULL;
    }

    new->hash = hash;
    new->size = size;
    new->count = 0;
    
    // initialize the lists to NULL
    for (size_t i = 0; i < size; i++)
        new->entries[i] = NULL;

    return new;
}

void ht_destroy(Hash_Table *ht, void (*destroy)(void *)) {
    if (ht == NULL || destroy == NULL)
        return;

    if (ht->entries != NULL) {
        struct bucket *temp = NULL, *aux;
        for (size_t i = 0; i < ht->size; i++) {
            temp = ht->entries[i];
            while (temp != NULL) {
                aux = temp->next;
                if (temp->data != NULL)
                    destroy(temp->data);

                if (temp->key != NULL)
                    free(temp->key);

                free(temp);
                temp = aux;
            }
        }

        free(ht->entries);
    }

    free(ht);
}

/**
 * @brief Calculates the load factor of the hash table
 * 
 * Assumes ht is not NULL
 * 
 * @param ht Hash Table
 * @return float Load factor
 */
static float ht_load_factor(const Hash_Table *ht) {
    return (float) ht->count / (float) ht->size;
}

/**
 * @brief Resizes the array from the hash table, it can grow or shrink
 * 
 * @param ht Hash Tables
 * @param change Indicates whether to grow or shrink, or no change
 */
static int ht_resize(Hash_Table *ht, short int change) {
    // no change to be made
    if (change == 0)
        return 0;

    size_t new_size = 2 * ht->size;
    if (change < 0)
        new_size /= 3;

    struct bucket **placeholder = (struct bucket **)malloc(new_size * sizeof(struct bucket *));
    if (placeholder == NULL)
        return 1;

    for (size_t i = 0; i < new_size; i++)
        placeholder[i] = NULL;

    struct bucket *temp = NULL, *aux = NULL;
    size_t index = 0;
    for (size_t i = 0; i < ht->size; i++) {
        temp = ht->entries[i];
        while (temp != NULL) {
            aux = temp->next;

            index = ht->hash(temp->key) % new_size;
            temp->next = placeholder[index];
            placeholder[index] = temp;

            temp = aux;
        }
    }
    
    free(ht->entries);
    ht->entries = placeholder;
    ht->size = new_size;

    return 0;
}

int ht_insert(Hash_Table *ht, void *data, const char *key) {
    if (ht == NULL || key == NULL)
        return 1;

    // load factor above 80%, double the size
    if (ht_load_factor(ht) > 0.8) {
        if (ht_resize(ht, GROW) != 0)
            return 3;
    }

    size_t index = ht->hash(key) % ht->size;
    struct bucket *temp = ht->entries[index];
    while (temp != NULL && strcmp(temp->key, key))
        temp = temp->next;

    // key does not exist on the table
    if (temp == NULL) {
        temp = create_bucket(data, key);
        if (temp == NULL)
            return 3;

        temp->next = ht->entries[index];
        ht->entries[index] = temp;
        ht->count++;

        return 0;
    }

    return 2;
}

void *ht_remove(Hash_Table *ht, const char *key) {
    if (ht == NULL || key == NULL)
        return NULL;

    if (ht_load_factor(ht) < 0.3) {
        if (ht_resize(ht, SHRINK) != 0)
            return NULL;
    }

    size_t index = ht->hash(key) % ht->size;
    struct bucket **temp = &(ht->entries[index]);
    while (*temp != NULL && strcmp((*temp)->key, key))
        temp = &((*temp)->next);
    
    void *result = NULL;
    // found the key
    if (*temp != NULL) {
        struct bucket *aux = (*temp)->next;
        result = (*temp)->data;

        if ((*temp)->key != NULL)
            free((*temp)->key);

        free(*temp);
        *temp = aux;
        ht->count--;
    }

    return result;
}

void *ht_lookup(const Hash_Table *ht, const char *key) {
    if (ht == NULL || key == NULL)
        return NULL;

    size_t index = ht->hash(key) % ht->size;
    struct bucket *temp = ht->entries[index];
    while (temp != NULL && strcmp(temp->key, key))
        temp = temp->next;

    void *result = NULL;
    if (temp != NULL)
        result = temp->data;

    return result;
}

bool ht_check(const Hash_Table *ht, const char *key) {
    if (ht == NULL || key == NULL)
        return false;

    size_t index = ht->hash(key) % ht->size;
    struct bucket *temp = ht->entries[index];
    while (temp != NULL && strcmp(temp->key, key))
        temp = temp->next;

    bool result = false;
    if (temp != NULL)
        result = true;

    return result;
}

size_t ht_elements(const Hash_Table *ht) {
    if (ht == NULL)
        return 0;
    return ht->count;
}

void ht_show(const Hash_Table *ht, void (*show)(const void *, const char *, FILE *), FILE *fp) {
    if (ht == NULL || show == NULL || fp == NULL)
        return;

    struct bucket *temp = NULL;
    for (size_t i = 0; i < ht->size; i++) {
        temp = ht->entries[i];
        if (temp)
            fprintf(fp, "----- index: %ld\n", i);
        while (temp != NULL) {
            show(temp->data, temp->key, fp);
            temp = temp->next;
        }
    }
}