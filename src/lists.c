/**
 * @file lists.c
 * @author Eduardo Fernandes (ef05238@gmail.com)
 * @brief Module that contains implementation of a Linked List
 * @version 0.1
 * @date 2024-10-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "lists.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * This module supports ordered List, functions that opperate under that
 * condition: llist_insert() llist_delete() (works on both) The remaining
 * function don't support such condition. Reminder NOT to mix both modes.
 */

typedef struct node {
    //! Stored object
    void *data;
    //! Pointer to the next node
    struct node *next;
} Node;

typedef struct l_list {
    //! List size
    unsigned int size;
    //! Function to compare elements
    int (*compare)(void *, void *);
    //! Function to duplicate elements
    void *(*duplicate)(void *);
    //! Function to free elements
    void (*free_data)(void *);
    //! Function to show elements
    void (*show_data)(void *);
    //! Nodes
    Node *head;
} LList;

Node *node_create(void *data) {
    Node *new = (Node *)calloc(1, sizeof(Node));
    assert(new); // is there memory??

    new->data = data;

    return new;
}

LList *llist_create(int (*compare)(void *, void *), void *(*duplicate)(void *),
                    void (*free_data)(void *), void (*show_data)(void *)) {
    LList *new = (LList *)calloc(1, sizeof(LList));
    assert(new); // is there memory??

    // atribute the functions
    new->compare = compare;
    new->duplicate = duplicate;
    new->free_data = free_data;
    new->show_data = show_data;

    return new;
}

void llist_insert(LList *list, void *data) {
    Node **temp = &(list->head);
    while (*temp && list->compare((*temp)->data, data) < 0)
        temp = &((*temp)->next);

    // create new node
    Node *new = node_create(data);
    // conect it to the list
    new->next = *temp;
    *temp = new;

    // increment the size of the list
    list->size++;
}

void llist_append(LList *list, void *data) {
    Node **temp = &(list->head);

    while (*temp)
        temp = &((*temp)->next);

    Node *new = node_create(data);
    new->next = *temp;
    *temp = new;

    // increment the size of the list
    list->size++;
}

void llist_prepend(LList *list, void *data) {
    Node *new = node_create(data);

    new->next = list->head;
    list->head = new;

    // increment the size of the list
    list->size++;
}

void *llist_delete(LList *list, void *data) {
    // list is empty
    if (list == NULL)
        return NULL;

    Node **temp = &(list->head);
    // go to the wanted node
    while (*temp && list->compare((*temp)->data, data) != 0)
        temp = &((*temp)->next);

    // end of the list
    if (*temp == NULL)
        return NULL;

    Node *aux_next = (*temp)->next;
    void *aux_data = (*temp)->data;
    // free the node
    free(*temp);
    *temp = aux_next;

    // decrement the size of the list
    list->size--;

    return aux_data;
}

void *llist_search(LList *list, void *data) {
    // list is empty
    if (list == NULL)
        return NULL;

    Node **temp = &(list->head);

    // go to the wanted node
    while (*temp && list->compare((*temp)->data, data) != 0)
        temp = &((*temp)->next);

    // end of the list
    if (*temp == NULL)
        return NULL;

    return list->duplicate((*temp)->data);
}

unsigned int llist_length(LList *list) { return list->size; }

bool llist_is_empty(LList *list) { return list == NULL || list->size == 0; }

LList *llist_clone(LList *list) {
    LList *new = llist_create(list->compare, list->duplicate, list->free_data,
                              list->show_data);
    Node **temp = &(new->head);
    Node *top = list->head;

    while (top) {
        *temp = node_create(list->duplicate(top->data));
        top = top->next;
        temp = &((*temp)->next);
    }

    *temp = NULL;
    return new;
}

void llist_destroy(LList *list) {
    Node *temp = NULL;

    while (list->head) {
        list->free_data(list->head->data);
        temp = list->head->next;
        free(list->head);
        list->head = temp;
    }

    free(list->head);
    free(list);
}

void llist_show(LList *list) {
    Node *temp = list->head;
    while (temp) {
        list->show_data(temp->data);
        printf("-> ");
        // printf("\n");
        temp = temp->next;
    }
    printf("X\n");
}

void *llist_min(LList *list) {
    // list is empty
    if (list == NULL)
        return NULL;

    // first element is the reference
    void *min = list->head->data;
    Node *temp = list->head;
    temp = temp->next;

    // go through the list
    while (temp) {
        // if there is one object smaller
        if (list->compare(temp->data, min) < 0)
            min = temp->data;

        temp = temp->next;
    }

    // allocate space for a duplicate
    // assume caller calls free
    return list->duplicate(min);
}

void *llist_max(LList *list) {
    // list is empty
    if (list == NULL)
        return NULL;

    // first element is the reference
    void *max = list->head->data;
    Node *temp = list->head;
    temp = temp->next;

    // go through the list
    while (temp) {
        // if there is one object smaller
        if (list->compare(temp->data, max) > 0)
            max = temp->data;

        temp = temp->next;
    }

    // allocate space for a duplicate
    // assume caller calls free
    return list->duplicate(max);
}

bool llist_is_ordered(LList *list) {
    // list is empty
    if (list->head == NULL)
        return true;

    Node *prev = list->head;
    Node *temp = list->head->next;

    while (temp && list->compare(prev->data, temp->data) < 0)
        temp = temp->next;

    if (temp)
        return false;

    return true;
}
