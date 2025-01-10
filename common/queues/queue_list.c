#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

struct chain {
    void *data;
    struct chain *next;
};

typedef struct queue {
    unsigned size;
    struct chain *front, *back;
} Queue;

struct chain *create_chain(void *data) {
    struct chain *new = (struct chain *)malloc(sizeof(struct chain));
    if (new == NULL)
        return NULL;

    *new = (struct chain){.data = data, .next = NULL};

    return new;
}

Queue *queue_create(void) {
    Queue *new = (Queue *)malloc(sizeof(struct queue));
    if (new == NULL)
        return NULL;

    *new = (Queue){.size = 0, .front = NULL, .back = NULL};

    return new;
}

void queue_destroy(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL)
        return;

    struct chain *temp = queue->front;
    while (temp != NULL) {
        queue->back = temp->next;

        if (temp->data)
            destroy(temp->data);
        temp = queue->back;
    }

    free(queue);
}

void enqueue(Queue *queue, void *data) {
    if (queue == NULL)
        return;

    struct chain *new_node = create_chain(data);
    // error handling ??
    if (new_node == NULL)
        return;

    // empty queue
    if (queue->front == NULL)
        queue->front = new_node;
    else {
        queue->back->next = new_node;
        queue->back = queue->back->next;
    }

    queue->size++;
}

void *dequeue(Queue *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    void *temp = queue->front->data;

    struct chain *aux = queue->front->next;
    free(queue->front);

    queue->front = aux;
    queue->size--;

    return temp;
}

void *queue_front(Queue *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    return queue->front->data;
}

void *queue_back(Queue *queue) {
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

    *queue = (struct queue){.size = 0, .front = NULL, .back = NULL};
}

unsigned queue_size(Queue *queue) {
    if (queue == NULL)
        return 0;

    return queue->size;
}
