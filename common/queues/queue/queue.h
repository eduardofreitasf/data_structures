#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

typedef struct queue Queue;

Queue *queue_create(void);
void queue_destroy(Queue *queue, void (*destroy)(void *));
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void *queue_front(Queue *queue);
void *queue_back(Queue *queue);
void queue_clear(Queue *queue, void (*destroy)(void *));
size_t queue_size(Queue *queue);
void show_queue(Queue *queue, void (*show)(const void *, FILE *), FILE *fp);

#endif
