#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Queue
 */
typedef struct queue Queue;

/**
 * @brief Allocates the necessary space for a Queue
 * 
 * @return Pointer to a Queue
 */
Queue *queue_create(void);

/**
 * @brief Frees the allocated space for a queue and it's elements
 * 
 * @param queue Pointer to a Queue
 * @param destroy Function to free the elements stored
 */
void queue_destroy(Queue *queue, void (*destroy)(void *));

/**
 * @brief Adds data to the end of the queue
 * 
 * @param queue Pointer to a Queue
 * @param data Data to store
 * @return 0 on sucess, 1 input is NULL, 2 allocation problems
 */
int enqueue(Queue *queue, void *data);

/**
 * @brief Removes the first element on a Queue
 * 
 * @param queue Pointer to a Queue
 * @return Data stored
 */
void *dequeue(Queue *queue);

/**
 * @brief Peek at the front of the Queue
 * 
 * @param queue Pointer to a Queue
 * @return Content stored at the front
 */
void *queue_front(const Queue *queue);

/**
 * @brief Peek at the back of the Queue
 * 
 * @param queue Pointer to a Queue
 * @return Content stored at the back
 */
void *queue_back(const Queue *queue);

/**
 * @brief Removes every element on the Queue
 * 
 * @param queue Pointer to a Queue
 * @param destroy Function to free the elements stored
 */
void queue_clear(Queue *queue, void (*destroy)(void *));

/**
 * @brief Determines the lenght of the Queue
 * 
 * @param queue Pointer to a Queue
 * @return Number of elements on the Queue
 */
size_t queue_size(const Queue *queue);

/**
 * @brief Checks if a Queue is empty
 * 
 * @param queue Pointer to a Queue
 * @return true Queue is empty
 * @return false Queue is not empty
 */
bool queue_is_empty(const Queue *queue);

/**
 * @brief Shows a Queue to fp
 * 
 * @param queue Pointer to a Queue
 * @param show Function to show the content stored
 * @param fp File pointer to output
 */
void show_queue(const Queue *queue, void (*show)(const void *, FILE *), FILE *fp);

#endif