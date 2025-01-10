#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <stddef.h>

/*
 * @brief Double ended queue
 */
typedef struct deque Deque;

/*
 * @brief Allocates the necessary space for a Double ended queue
 *
 * @return Allocated queue
 */
Deque *create_deque(void);

/*
 * @brief Frees the allocated space for the double ended queue
 *
 * If dq or destroy are NULL, no work is done
 */
void destroy_deque(Deque *dq, void (*destroy)(void *));

/*
 * @brief Adds data to the front of the queue
 * @param dq Double ended queue
 * @param data Content to be stored
 *
 * @return 0 opperation was successful
 *         1 allocation problems
 *         2 NULL pointer received
 */
int deque_push_front(Deque *dq, void *data);

/*
 * @brief Adds data to the back of the queue
 * @param dq Double ended queue
 * @param data Content to be stored
 *
 * @return 0 opperation was successful
 *         1 allocation problems
 *         2 NULL pointer received
 */
int deque_push_back(Deque *dq, void *data);

/*
 * @brief Removes the first element on the queue
 *
 * @param dq Double ended queue
 * @return Pointer to the content removed (NULL on failure)
 */
void * deque_pop_front(Deque *dq);

/*
 * @brief Removes the last element on the queue
 *
 * @param dq Double ended queue
 * @return Pointer to the content removed (NULL on failure)
 */
void * deque_pop_back(Deque *dq);

/*
 * @brief Calculates the size of the queue
 *
 *  If dq is NULL, the return value is 0
 *
 *  @param dq Double ended queue
 *  @return Length of the queue
 */
size_t deque_size(Deque *dq);

/*
 * @brief Inverts the order of the elements in the queue
 *
 * @param dq Double ended queue
 */
void deque_reverse(Deque *dq);

/*
 * @brief Checks if the queue is empty
 *
 * @return true Queue is empty
 * @return false Queue is not empty
 */
bool deque_is_empty(Deque *dq);

#endif
