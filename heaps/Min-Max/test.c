#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 100

void show_int(const void *data, FILE *fp) {
    if (data != NULL && fp != NULL)
        fprintf(fp, "%d ", *(int *)data);
}

void *create_int(int value) {
    int *new = malloc(sizeof(int));
    *new = value;

    return new;
}

int compare_int(const void *value1, const void *value2) {
    return *(int *)value1 - *(int *)value2;
}

int main(void) {
    srand(time(0));

    FILE *output = stdout;
    int temp = 0;
    void *trash = NULL;

    Heap *hp = create_heap(3);
    fprintf(output, "heap is empty: '%s'\n", heap_is_empty(hp) ? "true" : "false");

    
    fprintf(output, "--- INSERT ---\n");
    for (int i = 0; i < 15; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "insert %d\n", temp);
        heap_insert(hp, create_int(temp), &compare_int);
    }

    show_heap(hp, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "heap size: %lu\n", heap_size(hp));
    fprintf(output, "heap is empty: '%s'\n", heap_is_empty(hp) ? "true" : "false");

    fprintf(output, "--- REMOVE ---\n");
    for (int i = 0; i < 3; i++) {
        trash = heap_remove_root(hp, &compare_int);
        if (trash != NULL) {
            fprintf(output, "removed %d\n", *(int *)trash);
            free(trash);
        }
    }

    show_heap(hp, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "heap size: %lu\n", heap_size(hp));
    fprintf(output, "heap is empty: '%s'\n", heap_is_empty(hp) ? "true" : "false");

    destroy_heap(hp, &free);

    return 0;
}