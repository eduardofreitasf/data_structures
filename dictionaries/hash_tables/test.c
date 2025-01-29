#include "hash_table.h"
#include "hash_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <string.h>

#define STR_SIZE 9
#define MAX_VAL 100

void show_pair(const void *data, const char *key, FILE *fp) {
    fprintf(fp, "key: '%s' | value: %*d\n", key, 3, *(int *)data);
}

int main(void) {
    FILE *fp = stdout;
    // FILE *fp = fopen("result.log", "w");
    char *temp = NULL;
    int value = 0;

    Hash_Table * ht = ht_create(7, &fnv_hash);
    ht_show(ht, &show_pair, fp);

    fprintf(fp, "--- INSERT ---\n");
    for (int i = 0; i < 50; i++) {
        temp = random_string(STR_SIZE);
        value = rand() % MAX_VAL;
        ht_insert(ht, create(value), temp);
        free(temp);
    }

    temp = strdup("hello wor");
    value = rand() % MAX_VAL;
    ht_insert(ht, create(value), temp);
    free(temp);
    
    temp = strdup("eduardo f");
    value = rand() % MAX_VAL;
    ht_insert(ht, create(value), temp);
    free(temp);

    for (int i = 0; i < 5; i++) {
        temp = random_string(STR_SIZE);
        value = rand() % MAX_VAL;
        ht_insert(ht, create(value), temp);
        free(temp);
    }

    ht_show(ht, &show_pair, fp);
    fprintf(fp, "SIZE %ld\n", ht_elements(ht));

    fprintf(fp, "--- LOOKUP ---\n");
    int *result = ht_lookup(ht, "eduardo f");
    if (result != NULL)
        fprintf(fp, "key: '%s' | value: %d\n", "eduardo f", *result);
    else
        fprintf(fp, "NOT FOUND\n");

    result = ht_lookup(ht, "sdkfhds");
    if (result != NULL)
        fprintf(fp, "key: '%s' | value: %d\n", "sdkfhds", *result);
    else
        fprintf(fp, "NOT FOUND\n");

    fprintf(fp, "--- LOOKUP ---\n");

    bool found = ht_check(ht, "hello wor");
    fprintf(fp, "found '%s': '%s'\n", "hello wor", found ? "true" : "false");
    found = ht_check(ht, "kjjddd");
    fprintf(fp, "found '%s': '%s'\n", "kjjddd", found ? "true" : "false");

    fprintf(fp, "SIZE %ld\n", ht_elements(ht));
    fprintf(fp, "--- REMOVE ---\n");
    result = ht_remove(ht, "eduardo f");
    if (result != NULL)
        fprintf(fp, "key: '%s' | value: %d\n", "eduardo f", *result);

    result = ht_remove(ht, "hello wor");
    if (result != NULL)
        fprintf(fp, "key: '%s' | value: %d\n", "hello wor", *result);

    result = ht_remove(ht, "sdhfs");
    if (result != NULL)
        fprintf(fp, "key: '%s' | value: %d\n", "hello wor", *result);

    fprintf(fp, "SIZE %ld\n", ht_elements(ht));

    ht_destroy(ht, &free);
    fclose(fp);

    return 0;
}