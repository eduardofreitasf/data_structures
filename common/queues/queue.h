#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

Queue *queue_create(void);
void queue_destroy(Queue *queue, void (*destroy)(void *));
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void *queue_front(Queue *queue);
void *queue_back(Queue *queue);
void queue_clear(Queue *queue, void (*destroy)(void *));
unsigned queue_size(Queue *queue);

#endif
