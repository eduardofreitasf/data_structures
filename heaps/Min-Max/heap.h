#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Priority Queue (Heap)
 */
typedef struct heap Heap;

/**
 * @brief Creates a Priority Queue
 * 
 * @param size Initial size for the heap
 * @return Pointer to the heap
 */
Heap *create_heap(size_t size);

/**
 * @brief Frees the allocated space for a Heap
 * 
 * @param hp Heap
 * @param destroy Function to free the stored data
 */
void destroy_heap(Heap *hp, void (*destroy)(void *));

/**
 * @brief Checks if a Heap is empty
 * 
 * @param hp Heap
 * @return true Heap is empty
 * @return false Heap is not empty
 */
bool heap_is_empty(const Heap *hp);

/**
 * @brief Adds data to the Heap
 * 
 * @param hp Heap
 * @param data Data to store
 * @param compare Function to compare data
 * @return 0 on sucess, 1 NULL input, 2 allocation problems
 */
int heap_insert(Heap *hp, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Remove the first element on the Queue
 * 
 * @param hp Heap
 * @param compare Function to compare data
 * @return Data stored
 */
void *heap_remove_root(Heap *hp, int (*compare)(const void *, const void *));

/**
 * @brief Determines the number of elements on the Heap
 * 
 * @param hp Heap
 * @return Number of elements on the Heap
 */
size_t heap_size(const Heap *hp);

/**
 * @brief Shows the Priority Queue
 * 
 * @param hp Heap
 * @param show Function to show data
 * @param fp File pointer
 */
void show_heap(const Heap *hp, void (*show)(const void *, FILE *), FILE *fp);

/**
 * @brief Turns an array into a Priority Queue
 * 
 * @param data Array
 * @param size Number of elements on the array
 * @param compare Function to compare data
 * @return Heap
 */
Heap *heapify(void **data, size_t size, int (*compare)(const void *, const void *));

#endif