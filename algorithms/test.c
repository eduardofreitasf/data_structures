#include "sorts.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100

typedef struct {
    char *name;
    int age;
} person;

person *create(char *name, int age) {
    person *new = malloc(sizeof(person));
    new->name = name;
    new->age = age;

    return new;
}

void destroy(person *p) {
    if (p != NULL)
        free(p);
}

int compare_int(const void *integer1, const void *integer2) {
    return *(size_t *)integer1 - *(size_t *)integer2;
}

void copy(void *dest, const void *src, size_t size, size_t n_memb) {
    for (size_t i = 0; i < n_memb; i++)
        memcpy(dest + i * size, src + i * size, size);
}

int main(void) {
    srand(time(0));

    size_t num_array[MAX];
    size_t i;
    FILE *fp = fopen("result.log", "w");

    for (i = 0; i < MAX; i++)
        num_array[i] = rand() % MAX;

    fprintf(fp, "[");
    for (i = 0; i < MAX; i++)
        fprintf(fp, "%ld,", num_array[i]);
    fprintf(fp, "]\n");

    fprintf(fp, "order: %s\n", is_ordered(num_array, sizeof(size_t), MAX, &compare_int) == true ? "true" : "false");

    heap_sort(num_array, sizeof(size_t), MAX, &compare_int);

    fprintf(fp, "[");
    for (i = 0; i < MAX; i++)
        fprintf(fp, "%ld,", num_array[i]);
    fprintf(fp, "]\n");

    fprintf(fp, "order: %s\n", is_ordered(num_array, sizeof(size_t), MAX, &compare_int) == true ? "true" : "false");

    size_t *r = malloc(sizeof(size_t));
    *r = 300;
    fprintf(fp, "index of %ld: %ld\n", *r, linear_search(num_array, sizeof(size_t), MAX, &compare_int, r));
    *r = rand() % MAX;
    fprintf(fp, "index of %ld: %ld\n", *r, linear_search(num_array, sizeof(size_t), MAX, &compare_int, r));

    fclose(fp);

    return 0;
}