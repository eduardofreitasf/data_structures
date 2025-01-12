#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdbool.h>

/*
 * This header file contains the implementation of a generic array,
 * capable of storing any data type. It's a dynamic implementation,
 * when the array is full, doubles in size. When the capacity of the array is less than
 * 30%, it reduces it's size to 2/3 of the original.
 */

/**
 * @brief Struct that represents a generic Array
 * This data structure stores any data type, but be aware, there might be memory
 * leaks if it's used to store pointers to structures
 */
typedef struct array Array;

/**
 * @brief Create an Array
 * 
 * @param size Byte size of each element to store
 * @param reserved_size Pre defined size to allocate
 * @return Array* Generated Array
 */
Array *create_array(size_t size, size_t reserved_size);

/**
 * @brief Frees the allocated space for an Array
 * 
 * @param array Array
 * @param free_segment indicates if it's suppose to free the data stored
 * @return void* if free_segment == false, returns the data stored
 */
void *destroy_array(Array *array, bool free_segment);

/**
 * @brief Adds data to the end of the Array
 * 
 * @param arr Array
 * @param data Data to be stored
 * @return int 0 -> operation successful
 *             1 -> arr is NULL
 *             2 -> allocation problems
 */
int _array_append(Array *arr, const void *data);

/**
 * @brief Adds data to the front of the Array
 * 
 * @param arr Array
 * @param data Data to be stored
 * @return int 0 -> operation successful
 *             1 -> arr is NULL
 *             2 -> allocation problems
 */
int _array_preppend(Array *arr, const void *data);

/**
 * @brief Removes the last element on the Array
 * 
 * @param arr Array
 * @param dest Stores the removed content
 * @return int 0 -> opperation successful
 *             1 -> empty array
 *             2 -> allocation problems 
 */
int array_pop(Array *arr, void *dest);

/**
 * @brief Determines the number of elements on the array
 * 
 * @param arr Array
 * @return size_t Size of the Array
 */
size_t array_size(Array *arr);

/**
 * @brief Inserts data at index position
 * 
 * @param arr Array
 * @param data Data to be stored
 * @param index Index to store
 * @return int 0 -> opperation successfull
 *             1 -> arr is NULL
 *             2 -> allocation problems
 */
int _array_insert(Array *arr, const void *data, size_t index);

/**
 * @brief Removes data stored on index position
 * 
 * @param arr Array
 * @param dest Place to store the content
 * @param index Index position to remove
 * @return int 0 -> opperation successfull
 *             1 -> empty array
 * @note The previous order is kept
 */
int array_remove(Array *arr, void *dest, size_t index);

/**
 * @brief Places the content stored at index position in dest
 * 
 * @param arr Array
 * @param index Index position to look
 * @param dest Place to store the content
 * @note if index is bigger then max size, index is now max
 */
void array_index(Array *arr, size_t index, void *dest);

/**
 * @brief Sorts an array, using qsort
 * 
 * @param arr Array
 * @param compare Function to compare content
 */
void array_sort(Array *arr, int (*compare)(const void *, const void *));

/**
 * @brief Outputs an array to fp
 * 
 * @param arr Array
 * @param show Function to show the content
 * @param fp File pointer to output
 */
void show_array(Array *arr, void (*show)(const void *, FILE *), FILE *fp);

#define array_append(arr, d) _array_append((arr), &(d))
#define array_preppend(arr, d) _array_preppend((arr), &(d))
#define array_insert(arr, d, i) _array_insert((arr), &(d), (i))

#endif

