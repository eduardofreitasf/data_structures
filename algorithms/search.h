#ifndef SEARCH_H
#define SEARCH_H

#include <sys/types.h>

ssize_t linear_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup);

ssize_t binary_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup);

#endif