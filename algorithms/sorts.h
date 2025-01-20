#ifndef SORTS_H
#define SORTS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Checks if an array is ordered
 * 
 * Complexity: O(N)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 * @return true Has order
 * @return false Does not have order
 */
bool is_ordered(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Sorts an array through bubble sort
 * 
 * Every iteration, pushs the largest element to the top of the array
 * 
 * Complexity: O(N^2)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void bubble_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Sorts an array through selection sort
 * 
 * Every iteration, selects the smallest element from a segment of the array, then puts it in it's place
 * 
 * Complexity: O(N^2)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void selection_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Sorts an array through insertion sort
 * 
 * Takes an element off the array, and inserts it, in an ordered array, that is being built at the beggining
 * 
 * Complexity: O(N^2)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void insertion_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Sorts an array through quick sort
 * 
 * Divides an array in two parts, first come the elements smaller than the pivot point, and then the bigger ones,
 * repeting this action to each part, results in an ordered array
 * 
 * 
 * Complexity: O(N*log(N)) (on average)
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void quick_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Sorts an array through merge sort
 * 
 * Splits the array in the middle, and sorts both sides, then merges the sorted segments. Turning this operations in recursion,
 * you get an ordered array.
 * 
 * Complexity: O(N*log(N))
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void merge_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));

/**
 * @brief Turns the array in a max heap, then successively, removes the biggest element and places it the correct place,
 * forming a sorted array
 * 
 * Complexity: O(N*log(N))
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
void heap_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *));


#endif
