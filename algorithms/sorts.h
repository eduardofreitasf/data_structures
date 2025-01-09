#ifndef SORTS_H
#define SORTS_H

#include <stdbool.h>
#include <stddef.h>

bool is_ordered(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void bubble_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void selection_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void insertion_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void quick_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void merge_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

void heap_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));


#endif
