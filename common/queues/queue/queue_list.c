#include "queue.h"
#include <stdlib.h>

/**
 * @brief Struct for a node in a Queue
 */
struct chain {
    void *data;
    struct chain *next;
};

typedef struct queue {
    size_t size;
    struct chain *front, *back;
} Queue;

/**
 * @brief Creates a node for a Queue
 * 
 * @param data Data to store in the node
 * @return Pointer to a node
 */
static struct chain *create_chain(void *data) {
    struct chain *new = (struct chain *)malloc(sizeof(struct chain));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = NULL;

    return new;
}

Queue *queue_create(void) {
    Queue *new = (Queue *)malloc(sizeof(struct queue));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->back = new->front = NULL;

    return new;
}

void queue_destroy(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL)
        return;

    struct chain *temp = queue->front;
    while (temp != NULL) {
        queue->back = temp->next;

        // free data
        if (temp->data != NULL)
            destroy(temp->data);

        free(temp);
        temp = queue->back;
    }

    free(queue);
}

int enqueue(Queue *queue, void *data) {
    if (queue == NULL)
        return 1;

    struct chain *new_node = create_chain(data);
    if (new_node == NULL)
        return 2;

    // empty queue
    if (queue->front == NULL) {
        queue->front = new_node;
        queue->back = new_node;
    }
    else {
        queue->back->next = new_node;
        queue->back = queue->back->next;
    }

    queue->size++;
    return 0;
}

void *dequeue(Queue *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    void *temp = queue->front->data;

    struct chain *aux = queue->front->next;
    free(queue->front);

    queue->front = aux;
    queue->size--;

    // removed the last element
    if (queue->size == 0)
        queue->back = queue->front = NULL;

    return temp;
}

void *queue_front(const Queue *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    return queue->front->data;
}

void *queue_back(const Queue *queue) {
    if (queue == NULL || queue->back == NULL)
        return NULL;

    return queue->back->data;
}

void queue_clear(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL || destroy == NULL)
        return;

    struct chain *temp = queue->front;
    while (temp != NULL) {
        queue->back = temp->next;

        if (temp->data)
            destroy(temp->data);

        free(temp);
        temp = queue->back;
    }

    queue->size = 0;
    queue->back = queue->front = NULL;
}

size_t queue_size(const Queue *queue) {
    if (queue == NULL)
        return 0;

    return queue->size;
}

bool queue_is_empty(const Queue *queue) {
    return queue != NULL && queue->size == 0 && queue->back == NULL && queue->front == NULL;
}

void show_queue(const Queue *queue, void (*show)(const void *, FILE *), FILE *fp) {
    if (queue == NULL || show == NULL || fp == NULL)
        return;

    struct chain *temp = queue->front;
    while (temp != NULL) {
        show(temp->data, fp);
        temp = temp->next;
    }
}
