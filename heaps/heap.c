#include "heap.h"
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 17

#define PARENT(i) (i - 1) / 2
#define LEFT(i) (2 * i) + 1
#define RGIHT(i) (2 * i) + 2

typedef struct heap {
    size_t size, count;
    void **data;
} Heap;

Heap *create_heap(size_t size) {
    Heap *new = (Heap *)malloc(sizeof(Heap));
    if (new == NULL)
        return NULL;

    if (size == 0)
        size = INIT_SIZE;

    new->data = (void **)malloc(size * sizeof(void *));
    if (new->data == NULL) {
        free(new);
        return NULL;
    }

    new->size = size;
    new->count = 0;

    return new;
}

void destroy_heap(Heap *hp, void (*destroy)(void *)) {
    if (hp == NULL || destroy == NULL)
        return;

    if (hp->data != NULL) {
        for (size_t i = 0; i < hp->count; i++) {
            if (hp->data[i] != NULL)
                destroy(hp->data[i]);
        }

        free(hp->data);
    }

    free(hp);
}

/**
 * @brief Swaps two values on an array
 * 
 * Assumes data is not NULL, index1 and index2 must be valid
 * 
 * @param data Array
 * @param index1 Index 1
 * @param index2 Index 2
 */
static void swap(void **data, size_t index1, size_t index2) {
    void *temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

/**
 * @brief Repeatedly swaps a node with its parent until the condition
 * of the heap is satisfied or the root is reached
 * 
 * Assumes data and compare are not NULL, and index is valid
 * 
 * @param data Array
 * @param index Index to bubble up
 * @param compare Function to compare data
 */
static void bubble_up(void **data, size_t index, int (*compare)(const void *, const void *)) {
    size_t father = PARENT(index);

    while (index > 0 && compare(data[index], data[father]) < 0) {
        swap(data, index, father);
        index = father;
        father = PARENT(index);
    }
}

int heap_insert(Heap *hp, void *data, int (*compare)(const void *, const void *)) {
    if (hp == NULL || hp->data == NULL || compare == NULL)
        return 1;

    // double the size when full
    if (hp->count == hp->size) {
        void **temp = (void **) realloc(hp->data, hp->size * 2 * sizeof(void *));
        if (temp == NULL)
            return 2;
        hp->size *= 2;
        hp->data = temp;
    }

    hp->data[hp->count] = data;
    bubble_up(hp->data, hp->count++, compare);

    return 0;
}

static void bubble_down(void **data, size_t index, size_t size, int (*compare)(const void *, const void *)) {
    size_t left = LEFT(index);
    size_t right = 0;

    while (left < size) {
        right = RGIHT(index);
        if (right < size && compare(data[right], data[left]) < 0)
            left = right;
        if (compare(data[index], data[left]) < 0)
            break;

        swap(data, index, left);
        index = left;
        left = LEFT(index);
    }
}

void *heap_remove_root(Heap *hp, int (*compare)(const void *, const void *)) {
    if (hp == NULL || hp->data == NULL || compare == NULL || hp->count == 0)
        return NULL;

    // SHRINK TO 2/3 OF THE ORIGINAL WHEN IT HITS 30%

    void *result = hp->data[0];
    swap(hp->data, 0, --(hp->count));
    bubble_down(hp->data, 0, hp->count, compare);

    return result;
}

size_t heap_size(const Heap *hp) {
    if (hp != NULL)
        return hp->count;
    return 0;
}

void show_heap(Heap *hp, void (*show)(const void *, FILE *), FILE *fp) {
    if (hp == NULL || show == NULL || fp == NULL)
        return;

    for (size_t i = 0; i < hp->count; i++)
        show(hp->data[i], fp);
}
