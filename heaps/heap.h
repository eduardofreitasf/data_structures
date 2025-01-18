#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdbool.h>

typedef struct heap Heap;

Heap *create_heap(size_t size);
void destroy_heap(Heap *hp, void (*destroy)(void *));

int heap_insert(Heap *hp, void *data, int (*compare)(const void *, const void *));
void *heap_remove_root(Heap *hp, int (*compare)(const void *, const void *));

size_t heap_size(const Heap *hp);

void show_heap(Heap *hp, void (*show)(const void *, FILE *), FILE *fp);

bool is_heap(const void **data, size_t size);
Heap *heapify(void **data, size_t size, int (*compare)(const void *, const void *));

#endif