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

typedef struct l_list {
    void *data;
    struct l_list *next;
} LList;

LList *llist_create(void *data) {
    LList *new = (LList *)calloc(1, sizeof(LList));
    assert(new); // is there memory??

    new->data = data;
    return new;
}

void llist_insert(LList **list, void *data, int (*compare)(void *, void *)) {
    while (*list && compare((*list)->data, data) < 0)
        list = &((*list)->next);

    // create new node
    LList *new = llist_create(data);
    // conect it to the list
    new->next = *list;
    *list = new;
}

void llist_append(LList *list, void *data) {
    LList **temp = &list;

    while (*temp)
        temp = &((*temp)->next);

    LList *new = llist_create(data);
    new->next = *temp;
    *temp = new;
}

void llist_prepend(LList *list, void *data) {
    LList *new = llist_create(data);

    new->next = list;
    list = new;
}

void *llist_delete(LList *list, void *data, int (*compare)(void *, void *)) {
    // list is empty
    if (list == NULL)
        return NULL;

    LList **temp = &list;

    // go to the wanted node
    while (*temp && compare((*temp)->data, data) != 0)
        temp = &((*temp)->next);

    // end of the list
    if (*temp == NULL)
        return NULL;

    LList *aux_next = (*temp)->next;
    void *aux_data = (*temp)->data;
    // free the node
    free(*temp);
    *temp = aux_next;

    return aux_data;
}

void *llist_search(LList *list, void *data, int (*compare)(void *, void *)) {
    // list is empty
    if (list == NULL)
        return NULL;

    LList **temp = &list;

    // go to the wanted node
    while (*temp && compare((*temp)->data, data) != 0)
        temp = &((*temp)->next);

    // end of the list
    if (*temp == NULL)
        return NULL;

    return (*temp)->data;
}

unsigned int llist_length(LList *list) {
    unsigned int count = 0;
    while (list) {
        list = list->next;
        count++;
    }

    return count;
}

bool llist_is_empty(LList *list) { return list == NULL; }

LList *llist_clone(LList *list, void *(*duplicate)(void *)) {
    LList *new = NULL, **temp = &new;

    while (list) {
        *temp = llist_create(duplicate(list->data));
        list = list->next;
        temp = &((*temp)->next);
    }

    *temp = NULL;
    return new;
}

void llist_destroy(LList *list, void (*free_data)(void *)) {
    LList *temp = NULL;

    while (list) {
        free_data(list->data);
        temp = list->next;
        free(list);
        list = temp;
    }
}

void llist_show(LList *list, void (*show_data)(void *)) {
    while (list) {
        show_data(list->data);
        printf("-> ");
        // printf("\n");
        list = list->next;
    }
    printf("X\n");
}

void *llist_min(LList *list, void *(*duplicate)(void *),
                int (*compare)(void *, void *)) {
    // list is empty
    if (list == NULL)
        return NULL;

    // first element is the reference
    void *min = list->data;
    list = list->next;

    // go through the list
    while (list) {
        // if there is one object smaller
        if (compare(list->data, min) < 0)
            min = list->data;

        list = list->next;
    }

    // allocate space for a duplicate
    // assume caller calls free
    return duplicate(min);
}

void *llist_max(LList *list, void *(*duplicate)(void *),
                int (*compare)(void *, void *)) {
    // list is empty
    if (list == NULL)
        return NULL;

    // first element is the reference
    void *max = list->data;
    list = list->next;

    // go through the list
    while (list) {
        // if there is one object smaller
        if (compare(list->data, max) > 0)
            max = list->data;

        list = list->next;
    }

    // allocate space for a duplicate
    // assume caller calls free
    return duplicate(max);
}
