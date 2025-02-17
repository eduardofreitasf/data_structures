#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Circular Queue
 */
typedef struct circular_queue CQueue;

/**
 * @brief Allocates space for a Circular Queue
 * 
 * @return Pointer to a Circular Queue
 */
CQueue *create_cqueue(void);

/**
 * @brief Frees the allocated space for a Circular Queue
 * 
 * @param cq Circular Queue
 * @param destroy Function to free the data stored
 */
void destroy_cqueue(CQueue *cq, void (*destroy)(void *));

/**
 * @brief Adds data to the back of the Queue
 * 
 * @param cq Circular Queue
 * @param data Data to be stored
 * @return 0 on sucess, 1 input is NULL, 2 allocation problems
 */
int cqueue_enqueue(CQueue *cq, void *data);

/**
 * @brief Removes the element on the front of the Queue
 * 
 * @param cq Circular Queue
 * @return Data stored in the node
 */
void *cqueue_dequeue(CQueue *cq);

/**
 * @brief Peek at the front of the Queue
 * 
 * @param cq Circular Queue
 * @return Data stored at the front
 */
void *cqueue_front(const CQueue *cq);

/**
 * @brief Peek at the back of the Queue
 * 
 * @param cq Circular Queue
 * @return Data stored at the back
 */
void *cqueue_back(const CQueue *cq);

/**
 * @brief Removes every element on the Queue
 * 
 * @param cq Circular Queue
 * @param destroy Function to free the data stored
 */
void cqueue_clear(CQueue *cq, void (*destroy)(void *));

/**
 * @brief Determines the lenght of the Queue
 * 
 * @param cq Circular Queue
 * @return Number of elements on the Queue
 */
size_t cqueue_size(const CQueue *cq);

/**
 * @brief Checks if the Queue is empty
 * 
 * @param cq Circular Queue
 * @return true Queue is empty
 * @return false Queue is not empty
 */
bool cqueue_is_empty(const CQueue *cq);

/**
 * @brief Shows a Circular Queue
 * 
 * @param cq Circular Queue
 * @param show Function to show the content stored
 * @param fp File pointer to output
 */
void show_cqueue(const CQueue *cq, void (*show)(const void *, FILE *), FILE *fp);

#endif