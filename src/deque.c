#include "deque.h"
#include "node.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct deque {
    unsigned int size;
    // false:  front <-> back
    // true: back <-> front
    bool reversed;
    D_Node *front;
    D_Node *back;
    //! Function to duplicate elements
    void *(*duplicate)(void *);
    //! Function to free elements
    void (*free_data)(void *);
    //! Function to show elements
    void (*show_data)(void *);
} Deque;

Deque *deque_create(void *(*duplicate)(void *), void (*free_data)(void *),
                    void (*show_data)(void *)) {
    Deque *new = (Deque *)calloc(1, sizeof(Deque));
    assert(new); // is there memory ??

    new->duplicate = duplicate;
    new->free_data = free_data;
    new->show_data = show_data;

    return new;
}

unsigned int deque_size(Deque *deque) { return deque->size; }

bool deque_is_empty(Deque *deque) { return deque->size == 0; }

void deque_reverse(Deque *deque) { deque->reversed = !deque->reversed; }

void show_deque(Deque *deque) {
    D_Node *temp = NULL;

    if (deque->reversed) {
        temp = deque->back;
        while (temp) {
            deque->show_data(temp->data);
            temp = temp->prev;
        }
    } else {
        temp = deque->front;
        while (temp) {
            deque->show_data(temp->data);
            temp = temp->next;
        }
    }
}

void deque_destroy(Deque *deque) {
    D_Node *temp = NULL;
    while (deque->front) {
        temp = deque->front;
        deque->free_data(deque->front->data);
        free(deque->front);
        deque->front = temp;
    }
}