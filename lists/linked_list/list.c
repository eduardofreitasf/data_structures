#include "list.h"
#include <stdlib.h>

struct node {
    void *data;
    struct node *next;
};

typedef struct list {
    size_t size; // number of nodes
    struct node *head;
} List;

static struct node *create_node(void *data) {
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = NULL;

    return new;
}

List *list_create(void) {
    List *new = (List *)malloc(sizeof(struct list));
    if (new == NULL)
        return NULL;

    new->head = NULL;
    new->size = 0;

    return new;
}

void list_destroy(List *list, void (*destroy)(void *)) {
    if (list == NULL || destroy == NULL)
        return;

    struct node *temp = list->head, *aux = NULL;
    while (temp != NULL) {
        aux = temp->next;

        if (temp->data != NULL)
            destroy(temp->data);

        free(temp);
        temp = aux;
    }

    free(list);
}

int list_append(List *list, void *data) {
    if (list == NULL)
        return 1;

    struct node *new_node = create_node(data);
    if (new_node == NULL)
        return 2;

    struct node **temp = &(list->head);
    // go to the end of the list
    while (*temp != NULL)
        temp = &((*temp)->next);

    *temp = new_node;

    list->size++;

    return 0;
}

int list_preppend(List *list, void *data) {
    if (list == NULL)
        return 1;

    struct node *new_node = create_node(data);
    if (new_node == NULL)
        return 2;

    new_node->next = list->head;
    list->head = new_node;

    list->size++;

    return 0;
}

size_t list_size(const List *list) {
    if (list == NULL)
        return 0;

    return list->size;
}

bool list_is_empty(const List *list) { return list == NULL || list->size == 0; }

bool list_order(const List *list, int (*compare)(const void *, const void *)) {
    if (list == NULL || compare == NULL)
        return false;

    if (list->head == NULL)
        return true;

    bool result = true;
    struct node *temp = list->head;
    while (temp->next != NULL && result == true) {
        if (compare(temp->data, temp->next->data) > 0)
            result = false;

        temp = temp->next;
    }

    return result;
}

int list_insert(List *list, void *data,
                int (*compare)(const void *, const void *)) {
    if (list == NULL || compare == NULL)
        return 1;

    // add data to the head of the list
    if (list_order(list, compare) == false)
        return list_preppend(list, data);

    struct node **temp = &(list->head);
    while (*temp != NULL && compare((*temp)->data, data) < 0)
        temp = &((*temp)->next);

    struct node *new_node = create_node(data);
    if (new_node == NULL)
        return 2;

    new_node->next = *temp;
    *temp = new_node;
    list->size++;

    return 0;
}

void *list_remove(List *list, const void *key,
                  int (*compare)(const void *, const void *)) {
    if (list == NULL || compare == NULL)
        return NULL;

    struct node **temp = &(list->head);
    while (*temp != NULL && compare((*temp)->data, key) != 0)
        temp = &((*temp)->next);

    void *result = NULL;
    // found the key
    if (*temp != NULL && compare((*temp)->data, key) == 0) {
        result = (*temp)->data;

        struct node *aux = (*temp)->next;
        free(*temp);
        *temp = aux;
        list->size--;
    }

    return result;
}

List *list_clone(List *list, void *(*clone)(const void *)) {
    List *new_list = list_create();
    if (new_list == NULL || list == NULL)
        return NULL;

    struct node *temp = list->head;
    struct node **build = &(new_list->head);
    while (temp != NULL) {
        *build = create_node(clone(temp->data));
        if (*build == NULL) {
            // loop through the new list and free it
            return NULL;
        }

        temp = temp->next;
        build = &((*build)->next);
    }

    *build = NULL;
    new_list->size = list->size;

    return new_list;
}

void list_reverse(List *list) {
    if (list == NULL)
        return;

    struct node *temp = NULL, *result = NULL;
    while (list->head != NULL) {
        temp = list->head->next;
        list->head->next = result;
        result = list->head;
        list->head = temp;
    }

    list->head = result;
}

void *list_min(List *list, int (*compare)(const void *, const void *)) {
    if (list == NULL || list->head == NULL)
        return NULL;

    struct node *temp = list->head->next;
    void *min = list->head->data;
    while (temp != NULL) {
        if (compare(temp->data, min) < 0)
            min = temp->data;

        temp = temp->next;
    }

    return min;
}

void *list_max(List *list, int (*compare)(const void *, const void *)) {
    if (list == NULL || list->head == NULL)
        return NULL;

    struct node *temp = list->head->next;
    void *max = list->head->data;

    while (temp != NULL) {
        if (compare(temp->data, max) > 0)
            max = temp->data;

        temp = temp->next;
    }

    return max;
}

List *list_take(List *list, size_t size) {
    if (list == NULL || list->head == NULL)
        return NULL;

    struct node **remainder = &(list->head);
    size_t length = 0;
    while (size > 0 && length < list->size && *remainder != NULL) {
        remainder = &((*remainder)->next);
        size--;
        length++;
    }

    List *result = list_create();
    if (result == NULL)
        return NULL;

    result->size = list->size - length;
    list->size = length;
    result->head = *remainder;
    *remainder = NULL;

    return result;
}

List *list_drop(List *list, size_t size) {
    if (list == NULL || list->head == NULL)
        return NULL;

    List * result = list_create();
    if (result == NULL || size == 0)
        return result;

    result->head = list->head;
    struct node **temp = &(list->head);
    while (size > 0 && result->size < list->size && *temp != NULL) {
        temp = &((*temp)->next);
        size--;
        result->size++;
    }

    list->head = *temp;
    list->size = list->size - result->size;
    *temp = NULL;

    return result;
}

List *list_concat(List *list1, List *list2) {
    if (list1 == NULL && list2 == NULL)
        return NULL;

    if (list1 == NULL || list1->head == NULL)
        return list2;

    if (list2 == NULL || list2->head == NULL)
        return list1;

    // go to the end of the list
    struct node *temp = list1->head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = list2->head;
    list1->size += list2->size;

    return list1;
}

void show_list(List *list, void (*show)(const void *, FILE *), FILE *fp) {
    if (list == NULL || show == NULL || fp == NULL)
        return;

    struct node *temp = list->head;
    while (temp != NULL) {
        show(temp->data, fp);
        temp = temp->next;
    }
}