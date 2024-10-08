/**
 * @file lists.h
 * @author your name (ef05238@gmail.com)
 * @brief Module that contains declarations for Lists
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>

/**
 * @brief Node
 *
 */
typedef struct node Node;

/**
 * @brief Creates a Node with data stored
 *
 * @param data
 * @return Node*
 */
Node *node_create(void *data);

/**
 * @brief Linked List
 *
 */
typedef struct l_list LList;

/**
 * @brief Creates a Linked List
 *
 * @param compare Function to compare elements
 * @param duplicate Function to duplicate elements
 * @param free_data Function to free elements
 * @param show_data Function to show elements
 * @return LList* Linked List
 */
LList *llist_create(int (*compare)(void *, void *), void *(*duplicate)(void *),
                    void (*free_data)(void *), void (*show_data)(void *));

/**
 * @brief Inserts an element in a Linked List (with order)
 *
 * @param list Linked List
 * @param data Data to be stored
 */
void llist_insert(LList *list, void *data);

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
 * @return void* Null if it does not belong to List
 */
void *llist_delete(LList *list, void *data);

/**
 * @brief Looks for an element on a Linked List
 *
 * @param list Linked List
 * @param data Element to loom for
 * @return void* Null if it does not belong to List
 */
void *llist_search(LList *list, void *data);

/**
 * @brief Calculates the length of a Linked List
 *
 * @param list Linked List
 * @return unsigned int Length
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
 * @return LList* Copied Linked List
 */
LList *llist_clone(LList *list);

/**
 * @brief Frees the allocated space from a List
 *
 * @param list Linked List
 */
void llist_destroy(LList *list);

/**
 * @brief Shows a Linked List
 *
 * @param list Linked List
 */
void llist_show(LList *list);

/**
 * @brief Determines the minimum value in a Linked List
 *
 * @param list Linked List
 * @return void* Minimum object
 */
void *llist_min(LList *list);

/**
 * @brief Determines the maximum value in a Linked List
 *
 * @param list Linked List
 * @return void* Maximum object
 */
void *llist_max(LList *list);

/**
 * @brief Checks if a List is ordered
 *
 * @param list Linked List
 * @return true Is ordered
 * @return false Not ordered
 */
bool llist_is_ordered(LList *list);

#endif