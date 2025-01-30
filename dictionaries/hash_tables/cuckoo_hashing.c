#include "hash_table.h"
#include "hash_functions.h"
#include <stdlib.h>
#include <string.h>

/*
 * I have one array, with 2 * ht->size, when I insert I do ht->size * (count % 2) + index
 * count is the iterations I have done
 */

#define DEFAULT_SIZE 17


#define GROW 1
#define SHRINK (-1)
#define CLEAN 0


struct bucket {
    void *data;
    char *key;
    bool status;
};

typedef struct hash_table {
    size_t size, count;
    struct bucket *table;
    size_t (*hash1)(const char *);
    size_t (*hash2)(const char *); // predefined hash function
} Hash_Table;

Hash_Table *ht_create(size_t size, size_t (*hash)(const char *)) {
    if (hash == NULL)
        return NULL;
    Hash_Table *new = (Hash_Table *)malloc(sizeof(Hash_Table));
    if (new == NULL)
        return NULL;

    if (size == 0)
        size = DEFAULT_SIZE;

    new->table = (struct bucket *)malloc(2 * size * sizeof(struct bucket));
    if (new->table == NULL) {
        free(new);
        return NULL;
    }

    // initialize the buckets to free
    for (size_t i = 0; i < 2 * size; i++) {
        new->table[i].status = false;
        new->table[i].key = NULL;
        new->table[i].data = NULL;
    }

    new->size = size;
    new->count = 0;
    new->hash1 = hash;
    new->hash2 = &character_folding;

    return new;
}

void ht_destroy(Hash_Table *ht, void (*destroy)(void *)) {
    if (ht != NULL && destroy != NULL) {
        if (ht->table != NULL) {
            for (size_t i = 0; i < 2 * ht->size; i++) {
                if (ht->table[i].status == true) {
                    if (ht->table[i].data != NULL)
                        destroy(ht->table[i].data);

                    if (ht->table[i].key != NULL)
                        free(ht->table[i].key);
                }
            }

            free(ht->table);
        }

        free(ht);
    }
}

/**
 * @brief 
 * 
 * @param ht 
 * @param change 
 * @return int 
 */
static int ht_rehash(Hash_Table *ht, int change) {
    size_t new_size = ht->size;
    if (change == GROW)
        new_size *= 2;
    else if (change == SHRINK) {
        new_size *= 2;
        new_size /= 3;
    }

    struct bucket *new_buckets = (struct bucket *)malloc(2 * new_size * sizeof(struct bucket));
    if (new_buckets == NULL)
        return 1;

    size_t i = 0;
    // initialize the buckets to empty
    for (i = 0; i < 2 * new_size; i++) {
        new_buckets[i].status = false;
        new_buckets[i].key = NULL;
        new_buckets[i].data = NULL;
    }

    void *data = NULL;
    char *key = NULL;
    size_t index = 0, j = 0;
    // jump between the two tables
    for (i = 0; i < 2 * ht->size; i++) {
        index = ht->hash1(ht->table[i].key) % new_size;

        for (j = 0; j < new_size && new_buckets[new_size * (j % 2) + index].status == true; j++) {
            // switch the content of the buckets
            data = new_buckets[new_size * (j % 2) + index].data;
            key = new_buckets[new_size * (j % 2) + index].key;

            new_buckets[new_size * (j % 2) + index].data = ht->table[i].data;
            new_buckets[new_size * (j % 2) + index].key = ht->table[i].key;

            ht->table[i].data = data;
            ht->table[i].key = key;

            // select the hash function and calculate the index
            index = (j % 2 == 0 ? ht->hash1(key) : ht->hash2(key)) % new_size;
        }

        // place the content in the right place
        new_buckets[new_size * (j % 2) + index].status = true;
        new_buckets[new_size * (j % 2) + index].key = ht->table[i].key;
        new_buckets[new_size * (j % 2) + index].data = ht->table[i].data;
    }

    free(ht->table);
    ht->table = new_buckets;
    ht->size = new_size;

    return 0;
}

void ht_set_hash(Hash_Table *ht, size_t (*hash)(const char *)) {
    if (ht != NULL && hash) {
        ht->hash1 = hash;
        ht_rehash(ht, CLEAN);
    }
}


/**
 * @brief 
 * 
 * @param ht 
 * @param change 
 * @return float 
 */
static float ht_load_factor(const Hash_Table * ht) {
    if (ht != NULL)
        return (float) ht->count / (float) (2 * ht->size);
    return 0;
}

int ht_insert(Hash_Table *ht, void *data, const char *key) {
    if (ht == NULL || key == NULL || data == NULL)
        return 1;

    if (ht_load_factor(ht) > 0.8) {
        if (ht_rehash(ht, GROW) != 0)
            return 2;
    }

    void *temp_data = NULL;
    char *temp_key = NULL;
    char *aux = strdup(key);

    size_t count = 0, index = ht->hash1(key) % ht->size;
    // stops when it finds a free position
    // jumps between the two tables
    for (count = 0; count < ht->size && ht->table[ht->size * (count % 2) + index].status == true; count++) {
        temp_data = ht->table[ht->size * (count % 2) + index].data;
        temp_key = ht->table[ht->size * (count % 2) + index].key;

        ht->table[ht->size * (count % 2) + index].data = data;
        ht->table[ht->size * (count % 2) + index].key = aux;

        data = temp_data;
        aux = temp_key;

        index = (count % 2 == 0 ? ht->hash1(temp_key) : ht->hash2(temp_key)) % ht->size;
    }

    // it's always true, just a failsafe
    if (count < ht->size) {
        ht->table[ht->size * (count % 2) + index].status = true;
        ht->table[ht->size * (count % 2) + index].key = aux;
        ht->table[ht->size * (count % 2) + index].data = data;

        ht->count++;
    } else {
        if (ht_rehash(ht, GROW) != 0)
            return 2;
        else
            ht_insert(ht, data, aux);
    }

    return 0;
}

void *ht_remove(Hash_Table *ht, const char *key) {
    void *result = NULL;
    if (ht != NULL && key != NULL) {
        size_t index = ht->hash1(key) % ht->size;
        if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0) {
            result = ht->table[index].data;
            free(ht->table[index].key);
            ht->table[index].status = false;

            ht->count--;
        } else {
            index = ht->hash2(key) % ht->size;
            if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0) {
                result = ht->table[index].data;
                free(ht->table[index].key);
                ht->table[index].status = false;
                
                ht->count--;
            }
        }
    }

    return result;
}

void *ht_lookup(const Hash_Table *ht, const char *key) {
    void *result = NULL;
    if (ht != NULL && key != NULL) {
        size_t index = ht->hash1(key) % ht->size;
        if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0)
            result = ht->table[index].data;
        else {
            index = ht->hash2(key) % ht->size;
            if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0)
                result = ht->table[index].data;
        }
    }

    return result;
}

bool ht_check(const Hash_Table *ht, const char *key) {
    bool result = false;
    if (ht != NULL && key != NULL) {
        size_t index = ht->hash1(key) % ht->size;
        if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0)
            result = true;
        else {
            index = ht->hash2(key) % ht->size;
            if (ht->table[index].status == true && strcmp(ht->table[index].key, key) == 0)
                result = true;
        }
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
        return;

    fprintf(fp, "\n--- First table ---\n\n");
    for (size_t i = 0; i < 2 * ht->size; i++) {
        if (i == ht->size)
            fprintf(fp, "\n--- Second table ---\n\n");

        if (ht->table[i].status == false)
            fprintf(fp, "Position %ld is FREE\n", i % ht->size);
        else
            show(ht->table[i].data, ht->table[i].key, fp);        
    }
}

void ht_refresh(Hash_Table *ht) {
    if (ht != NULL)
        ht_rehash(ht, CLEAN);
}