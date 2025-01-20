#ifndef SEARCH_H
#define SEARCH_H

#include <sys/types.h>

/**
 * @brief Determines the index in which lookup is
 * 
 * Complexity: O(N)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 * @param lookup Data to look for
 * @return -1 lookup does not occur in the array
 * @return size_t index of lookup
 */
ssize_t linear_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup);

/**
 * @brief Determines the index in which lookup is
 * 
 * Complexity: O(log(N))
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 * @param lookup Data to look for
 * @return -1 lookup does not occur in the array
 * @return size_t index of lookup
 */
ssize_t binary_search(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *), const void *lookup);

#endif