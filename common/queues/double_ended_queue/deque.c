#include "deque.h"
#include <stdlib.h>

/**
 * @brief Double ended node that stores generic data
 */
struct d_node {
    void *data;
    struct d_node *next, *prev;
};

typedef struct deque {
    size_t size;
    bool reverse;
    struct d_node *front, *back;
} Deque;

/**
 * @brief Allocates space for a double ended node
 * 
 * @param data Data to store in the node
 * @return pointer to the node
 */
static struct d_node *create_double_node(void *data) {
    struct d_node *new = (struct d_node *) malloc(sizeof(struct deque));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = new->prev = NULL;

    return new;
}

Deque *create_deque(void) {
    Deque *new = (struct deque *) malloc(sizeof(struct deque));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->reverse = false;
    new->back = new->front = NULL;

    return new;
}

void destroy_deque(Deque *dq, void (*destroy)(void *)) {
    if (dq == NULL || destroy == NULL)
        return;

    struct d_node *temp = dq->front, *aux = NULL;
    while (temp != NULL) {
        aux = temp->next;
        if (temp->data != NULL)
            destroy(temp->data);

        free(temp);
        temp = aux;
    }

    free(dq);
}

size_t deque_size(const Deque *dq) {
    return dq == NULL ? 0 : dq->size;
}

void deque_reverse(Deque *dq) {
    if (dq != NULL)
        dq->reverse = !(dq->reverse);
}

/**
 * @brief Adds data to the front of the queue
 * 
 * @note assumes dq is not NULL
 * @param dq Pointer to a Double ended queue
 * @param data Data to store
 * @return 0 on sucess
 *         1 allocation problems
 */
static int push_front(Deque *dq, void *data) {
    struct d_node *new_node = create_double_node(data);
    if (new_node == NULL)
        return 1;

    new_node->next = dq->front;
    if (dq->front != NULL)
        dq->front->prev = new_node;
    dq->front = new_node;

    // empty deque
    if (dq->back == NULL)
        dq->back = new_node;

    dq->size++;

    return 0;
}

/**
 * @brief Adds data to the back of the queue
 * 
 * @note assumes dq is not NULL
 * @param dq Pointer to a Double ended queue
 * @param data Data to store
 * @return 0 on sucess
 *         1 allocation problems
 */
static int push_back(Deque *dq, void *data) {
    struct d_node *new_node = create_double_node(data);
    if (new_node == NULL)
        return 1;

    new_node->prev = dq->back;
    if (dq->back != NULL)
        dq->back->next = new_node;
    dq->back = new_node;
    
    // empty deque
    if (dq->front == NULL)
        dq->front = new_node;

    dq->size++;

    return 0;
}

/**
 * @brief Removes the front element of the queue
 * 
 * @note assumes dq is not NULL
 * @param dq Pointer to the double ended queue
 * @return data stored on the node
 */
static void * pop_front(Deque *dq) {
    // empty deque
    if (dq->front == NULL)
       return NULL;

    void *temp = dq->front->data;
    struct d_node *temp_node = dq->front->next;
    free(dq->front);
    
    dq->front = temp_node;
    if (temp_node != NULL)
        temp_node->prev = NULL;

    dq->size--;
    if (dq->size == 0) {
        dq->back = NULL;
        dq->front = NULL;
    }

    return temp;
}

/**
 * @brief Removes the back element of the queue
 * 
 * @note assumes dq is not NULL
 * @param dq Pointer to the double ended queue
 * @return data stored on the node
 */
static void * pop_back(Deque *dq) {
    // empty deque
    if (dq->back == NULL)
       return NULL;

    void *temp = dq->back->data;
    struct d_node *temp_node = dq->back->prev;
    free(dq->back);

    dq->back = temp_node;
    if (temp_node != NULL)
        temp_node->next = NULL;

    dq->size--;
    if (dq->size == 0) {
        dq->back = NULL;
        dq->front = NULL;
    }

    return temp;
}

int deque_push_front(Deque *dq, void *data) {
    if (dq == NULL)
        return 2;

    return dq->reverse == false ? push_front(dq, data) : push_back(dq, data);
}

int deque_push_back(Deque *dq, void *data) {
    if (dq == NULL)
        return 2;

    return dq->reverse == false ? push_back(dq, data) : push_front(dq, data);
}

void * deque_pop_front(Deque * dq) {
    if (dq == NULL)
        return NULL;

    return dq->reverse == false ? pop_front(dq) : pop_back(dq);
}

void * deque_pop_back(Deque * dq) {
    if (dq == NULL)
        return NULL;

    return dq->reverse == false ? pop_back(dq) : pop_front(dq);
}

void *deque_front(const Deque *dq) {
    if (dq != NULL && dq->front != NULL)
        return dq->front->data;

    return NULL;
}

void *deque_back(const Deque *dq) {
    if (dq != NULL && dq->back != NULL)
        return dq->back->data;

    return NULL;
}

bool deque_is_empty(const Deque *dq) {
    return dq == NULL || dq->size == 0;
}

void show_deque(const Deque *dq, void (*show)(const void *, FILE *), FILE *fp) {
    if (dq == NULL || show == NULL || fp == NULL)
        return;
    
    struct d_node *temp = NULL;
    if (dq->reverse == true) {
        temp = dq->back;
        while (temp != NULL) {
            show(temp->data, fp);
            temp = temp->prev;
        }
    } else {
        temp = dq->front;
        while (temp != NULL) {
            show(temp->data, fp);
            temp = temp->next;
        }
    }
}