#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct circular_queue CQueue;

CQueue *create_cqueue(void);
void destroy_cqueue(CQueue *cq, void (*destroy)(void *));

int cqueue_enqueue(CQueue *cq, void *data);
void *cqueue_dequeue(CQueue *cq);

void *cqueue_front(CQueue *cq);
void *cqueue_back(CQueue *cq);

void cqueue_clear(CQueue *cq, void (*destroy)(void *));
size_t cqueue_size(CQueue *cq);
bool cqueue_is_empty(CQueue *cq);
void show_cqueue(CQueue *cq, void (*show)(const void *, FILE *), FILE *fp);

#endif