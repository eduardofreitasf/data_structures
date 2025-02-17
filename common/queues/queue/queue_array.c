#include "queue.h"
#include <stdlib.h>

#define GROW 1
#define SHRINK (-1)
#define CLEAN 0

typedef struct queue {
    size_t size, front, length;
    void **data;
} Queue;

Queue *queue_create(void) {
    Queue *new = (Queue *)malloc(sizeof(struct queue));
    if (new == NULL)
        return NULL;

    // original size is 1
    void **data = (void **)malloc(1 * sizeof(void *));
    if (data == NULL) {
        free(new);
        return NULL;
    }

    data[0] = NULL;

    new->size = 1;
    new->length = 0;
    new->front = 0;
    new->data = data;

    return new;
}

void queue_destroy(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL || destroy == NULL)
        return;

    size_t index = queue->front, i = 0;
    while (i++ < queue->length) {
        if (queue->data[index] != NULL)
            destroy(queue->data[index]);

        index = (index + 1) % queue->size;
    }

    if (queue->data != NULL)
        free(queue->data);

    free(queue);
}

/**
 * @brief Determines the load factor of a Queue
 * 
 * Assumes queue is not NULL
 * 
 * @param queue Pointer to a Queue
 * @return Load Factor
 */
static float queue_load_factor(Queue *queue) {
    return (float)queue->length / (float)queue->size;
}

/**
 * @brief Allocates more/less space for a Queue
 * 
 * Assumes queue and queue->data are not NULL
 * 
 * @param queue Pointer to a Queue
 * @param growth Flag to grow/shrink/clean the Queue
 * @return 0 on sucess, 1 allocation problems
 */
static int queue_resize(Queue *queue, int growth) {
    // double the size
    size_t new_size = queue->size;
    if (growth > 0)
        new_size *= 2;
    else if (growth < 0) {
        // resize to 2/3
        new_size *= 2;
        new_size /= 3;
    }

    void **temp = (void **)malloc(new_size * sizeof(void *));
    if (temp == NULL)
        return 1;

    size_t index = queue->front;
    // fill the new table, starting at position 0
    for (size_t i = 0; i < queue->length; i++) {
        temp[i] = queue->data[index];
        index = (index + 1) % queue->size;
    }

    free(queue->data);

    queue->front = 0;
    queue->size = new_size;
    queue->data = temp;

    return 0;
}

int enqueue(Queue *queue, void *data) {
    if (queue == NULL || queue->data == NULL)
        return 1;

    // queue is full
    if (queue->length == queue->size) {
        if (queue_resize(queue, GROW) != 0)
            return 2;
    }

    queue->data[(queue->front + queue->length++) % queue->size] = data;
    return 0;
}

void *dequeue(Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    void *temp = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    queue->length--;

    // queue has less than 30%
    if (queue_load_factor(queue) < 0.3)
        if (queue_resize(queue, SHRINK) != 0)
            return NULL;

    return temp;
}

void *queue_front(const Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    return queue->data[queue->front];
}

void *queue_back(const Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    return queue->data[(queue->front + queue->length - 1) % queue->size];
}

void queue_clear(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL || queue->data == NULL || destroy == NULL)
        return;

    size_t i = 0;
    while (i < queue->length) {
        if (queue->data[i] != NULL)
            destroy(queue->data[i]);
        i++;
    }

    queue->front = 0;
    queue->length = 0;
}

size_t queue_size(const Queue *queue) {
    if (queue == NULL)
        return 0;

    return queue->length;
}

bool queue_is_empty(const Queue *queue) {
    return queue != NULL && queue->length == 0;
}
void show_queue(const Queue *queue, void (*show)(const void *, FILE *), FILE *fp) {
    if (queue == NULL || show == NULL || fp == NULL)
        return;

    for (size_t i = 0, index = queue->front; i < queue->length; i++) {
        show(queue->data[index], fp);
        index = (index + 1) % queue->size;            
    }
}
