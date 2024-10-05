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
LList *llist_create(void *data);

/**
 * @brief Inserts an element in a Linked List (with order)
 *
 * @param list Linked List
 * @param data Data to be stored
 * @param compare Function to compare elements on the List
 * @return true If insertion was sucessfull
 * @return false If insertion was not possible
 */
bool llist_insert(LList *list, void *data, int (*compare)(void *, void *));

/**
 * @brief Inserts an element at the end of a List
 *
 * @param list Linked List
 * @param data Data to be stored
 */
void llist_append(LList *list, void *data);

/**
 * @brief Inserts an element at the head of a List
 *
 * @param list Linked List
 * @param data Data to be stored
 */
void llist_prepend(LList *list, void *data);

/**
 * @brief Deletes an element from a Linked List
 *
 * @param list Linked List
 * @param data Element to look for
 * @param compare Function to compare elements on a List
 * @return void* Null if it does not belong to List
 */
void *llist_delete(LList *list, void *data, int (*compare)(void *, void *));

/**
 * @brief Looks for an element on a Linked List
 *
 * @param list Linked List
 * @param data Element to loom for
 * @param compare Function to compare elements on a List
 * @return void* Null if it does not belong to List
 */
void *llist_search(LList *list, void *data, int (*compare)(void *, void *));

/**
 * @brief Calculates the length of a Linked List
 *
 * @param list Linked List
 * @return unsigned int length
 */
unsigned int llist_length(LList *list);

/**
 * @brief Tests if a List is empty
 *
 * @param list Linked List
 * @return true List is empty
 * @return false List isn't empty
 */
bool llist_is_empty(LList *list);

/**
 * @brief Creates an identical Linked List
 *
 * @param list Linked List
 * @param duplicate Function to duplicate data
 * @return LList* Copied Linked List
 */
LList *llist_clone(LList *list, void *(*duplicate)(void *));

/**
 * @brief Frees the allocated space from a List
 *
 * @param list Linked List
 * @param free_data Function to free each object
 */
void llist_destroy(LList *list, void (*free_data)(void *));

/**
 * @brief Shows a Linked List
 *
 * @param list Linked List
 * @param show_data Function to show each object
 */
void show_llist(LList *list, void (*show_data)(void *));

/**
 * @brief Determines the minimum value in a Linked List
 *
 * @param list Linked List
 * @param duplicate Function to duplicate an object
 * @param compare Function to compare objects
 * @return void* Minimum object
 */
void *llist_min(LList *list, void *(*duplicate)(void *),
                int (*compare)(void *, void *));

/**
 * @brief Determines the maximum value in a Linked List
 *
 * @param list Linked List
 * @param duplicate Function to duplicate an object
 * @param compare Function to compare objects
 * @return void* maximum object
 */
void *llist_max(LList *list, void *(*duplicate)(void *),
                int (*compare)(void *, void *));

#endif