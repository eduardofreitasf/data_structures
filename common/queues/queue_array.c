#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct queue {
    unsigned size, front, length;
    void **data;
} Queue;

Queue *queue_create(void) {
    Queue *new = (Queue *)malloc(sizeof(struct queue));
    if (new == NULL)
        return NULL;

    void **data = (void **)malloc(1 * sizeof(void *));
    if (data == NULL) {
        free(new);
        return NULL;
    }

    *new = (Queue){.size = 1, .front = 0, .length = 0, .data = data};

    return new;
}

void queue_destroy(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL || destroy == NULL)
        return;

    unsigned i = queue->front;
    while (queue->length-- >= 0) {
        if (queue->data[i] != NULL)
            destroy(queue->data[i]);

        i = (i + 1) % queue->size;
    }

    if (queue->data != NULL)
        free(queue->data);

    free(queue);
}

float queue_load_factor(Queue *queue) {
    if (queue == NULL)
        return 0;

    return (float)queue->length / (float)queue->size;
}

int queue_resize(Queue *queue, bool growth) {
    if (queue == NULL)
        return 1;

    // double the size
    if (growth == true) {
        queue->size *= 2;
    } else {
        // resize to 2/3
        if (queue_load_factor(queue) < 2.0 / 3.0) {
            queue->size *= 2;
            queue->size /= 3;
        } else
            return 2;
    }

    queue->data = realloc(queue->data, queue->size * sizeof(void *));
    if (queue->data == NULL)
        return 3;

    return 0;
}

void enqueue(Queue *queue, void *data) {
    if (queue == NULL)
        return;

    if (queue->length == queue->size) {
        int result = queue_resize(queue, true); // error handling ??
        if (result == 3)
            return;
    }

    queue->data[(queue->front + queue->length++) % queue->size] = data;
}

void queue_cleanup(Queue *queue) {
    if (queue == NULL || queue->data)
        return;

    void **new_data = (void **)malloc(queue->size * sizeof(void *));
    // error handling ??
    if (new_data == NULL)
        return;

    unsigned i = 0;
    while (i < queue->length) {
        new_data[i] = queue->data[(queue->front + i) % queue->size];
        i++;
    }

    free(queue->data);
    queue->front = 0;
    queue->data = new_data;
}

void *dequeue(Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    void *temp = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    queue->length--;

    if (queue_load_factor(queue) < 0.3) {
        queue_cleanup(queue);
        queue_resize(queue, false);
    }

    return temp;
}

void *queue_front(Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    return queue->data[queue->front];
}

void *queue_back(Queue *queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0)
        return NULL;

    return queue->data[(queue->front + queue->length) % queue->size];
}

void queue_clear(Queue *queue, void (*destroy)(void *)) {
    if (queue == NULL || queue->data == NULL || destroy == NULL)
        return;

    unsigned i = 0;
    while (i < queue->length) {
        if (queue->data[i] != NULL)
            destroy(queue->data[i]);
        i++;
    }
}

unsigned queue_size(Queue *queue) {
    if (queue == NULL)
        return 0;

    return queue->length;
}
