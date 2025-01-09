#include "search.h"

ssize_t linear_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup) {
    size_t i = 0;
    while (i < n_memb && compare(base + i * size, lookup) != 0)
        i++;
        
    if (i >= n_memb)
        return -1;
    return i;
}

ssize_t binary_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup) {
    size_t middle = 0, bottom = 0, top = n_memb - 1;
    while (bottom <= top) {
        middle = (top - bottom) / 2;
        if (compare(base + middle * size, lookup) == 0)
            return middle;

        if (compare(base + middle * size, lookup) < 0)
            bottom = middle + 1;
        else
            top = middle - 1;
    }

    return -1;
}