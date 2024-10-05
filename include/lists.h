#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>

/**
 * @brief Linked List
 * 
 */
typedef struct l_list LList;

/**
 * @brief Creates a node of a linked list
 * 
 * @param data Data to store
 * @return LList* Linked List
 */
LList * llist_create(void * data);

/**
 * @brief Inserts an element in a Linked List (with order)
 * 
 * @param list Linked List
 * @param data Data to be stored
 * @param compare Function to compare elements on the List
 * @return true If insertion was sucessfull
 * @return false If insertion was not possible
 */
bool llist_insert(LList * list, void *data, int (*compare)(void *, void *));

/**
 * @brief Inserts an element at the end of a List
 * 
 * @param list Linked List
 * @param data Data to be stored
 */
void llist_append(LList * list, void *data);

/**
 * @brief Inserts an element at the head of a List
 * 
 * @param list Linked List
 * @param data Data to be stored
 */
void llist_prepend(LList * list, void *data);

/**
 * @brief Deletes an element from a Linked List
 * 
 * @param list Linked List
 * @param data Element to look for
 * @param compare Function to compare elements on a List
 * @return void* 
 */
void * llist_delete(LList * list, void *data, int (*compare)(void *, void *));

/**
 * @brief Looks for an element on a Linked List
 * 
 * @param list Linked List
 * @param data Element to loom for
 * @param compare Function to compare elements on a List
 * @return LList* 
 */
LList * llist_search(LList * list, void *data, int (*compare)(void *, void *));


unsigned int llist_size(LList * list);


bool llist_is_empty(LList * list);


LList * llist_clone(LList * list, void *(*duplicate)(void *));


void llist_destroy(LList * list, void (*free_data)(void *));


void show_llist(LList * list, void (*show_data)(void *));


void *llist_min(LList * list, void *(*duplicate)(void *));


void *llist_max(LList * list, void *(*duplicate)(void *));

#endif