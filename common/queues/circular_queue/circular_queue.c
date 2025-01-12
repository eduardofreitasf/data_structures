#include "circular_queue.h"
#include <stdlib.h>

struct chain {
    void *data;
    struct chain *next;
};

typedef struct circular_queue {
    size_t size;
    struct chain *back;
} CQueue;

static struct chain *create_chain(void *data) {
    struct chain *new = (struct chain *)malloc(sizeof(struct chain));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = NULL;

    return new;
}

CQueue *create_cqueue(void) {
    CQueue *new = (CQueue *)malloc(sizeof(CQueue));
    if (new == NULL)
        return NULL;

    new->back = NULL;
    new->size = 0;

    return new;
}

void destroy_cqueue(CQueue *cq, void (*destroy)(void *)) {
    if (cq == NULL || destroy == NULL)
        return;

    if (cq->back != NULL) {
        struct chain *temp = cq->back->next;
        cq->back->next = NULL;
        while (temp != NULL) {
            cq->back = temp->next;
            if (temp->data != NULL)
                destroy(temp->data);
            
            free(temp);
            temp = cq->back;
        }
    }
}

int cqueue_enqueue(CQueue *cq, void *data) {
    if (cq == NULL)
        return 1;

    struct chain *new_node = create_chain(data);
    if (new_node == NULL)
        return 2;

    // queue is empty
    if (cq->back == NULL) {
        cq->back = new_node;
        cq->back->next = new_node;
    } else {
        new_node->next = cq->back->next;
        cq->back->next = new_node;
        cq->back = new_node;
    }
    cq->size++;

    return 0;
}

void *cqueue_dequeue(CQueue *cq) {
    if (cq == NULL || cq->back == NULL)
        return NULL;

    void *result = NULL;
    // size == 1
    if (cq->back->next == cq->back) {
        result = cq->back->data;
        cq->back->next = NULL;

        free(cq->back);
        cq->back = NULL;
    } else {
        struct chain *temp = cq->back->next;
        result = temp->data;
        cq->back->next = temp->next;
    
        free(temp);
    }
    cq->size--;

    return result;
}

void *cqueue_front(CQueue *cq) {
    if (cq == NULL || cq->back == NULL)
        return NULL;

    return cq->back->next->data;
}

void *cqueue_back(CQueue *cq) {
    if (cq == NULL || cq->back == NULL)
        return NULL;

    return cq->back->data;    
}

void cqueue_clear(CQueue *cq, void (*destroy)(void *)) {
    if (cq == NULL || destroy == NULL)
        return;
    
    if (cq->back != NULL) {
        struct chain *temp = cq->back->next;
        cq->back->next = NULL;

        while (temp != NULL) {
            cq->back = temp->next;
            if (temp->data != NULL)
                destroy(temp->data);
            
            free(temp);
            temp = cq->back;
        }
        cq->back = NULL;
    }
    cq->size = 0;
}

size_t cqueue_size(CQueue *cq) {
    if (cq == NULL)
        return 0;
    return cq->size;
}

bool cqueue_is_empty(CQueue *cq) {
    return cq == NULL || cq->size == 0 || cq->back == NULL;
}

void show_cqueue(CQueue *cq, void (*show)(const void *, FILE *), FILE *fp) {
    if (cq == NULL || show == NULL || fp == NULL || cq->back == NULL)
        return;

    struct chain *temp = cq->back->next;
    size_t ite = 0;
    // first condition will never fail (but we never know)
    while (temp != NULL && ite < cq->size) {
        show(temp->data, fp);
        ite++;
        temp = temp->next;
    }
}