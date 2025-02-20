#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Linked List
 */
typedef struct list List;

/**
 * @brief Allocates the necessary space for a List
 * 
 * @return Pointer to a List
 */
List *list_create(void);

/**
 * @brief Frees the space occupied by a List and it's elements
 * 
 * @param list List
 * @param destroy Function to free the data
 */
void list_destroy(List *list, void (*destroy)(void *));

/**
 * @brief Adds data to the end of the List
 * 
 * @param list List
 * @param data Data to store
 * @return 0 on sucess, 1 input is NULL, 2 allocation problems
 */
int list_append(List *list, void *data);

/**
 * @brief Adds data to the front of the List
 * 
 * @param list List
 * @param data Data to store
 * @return 0 on sucess, 1 input is NULL, 2 allocation problems
 */
int list_preppend(List *list, void *data);

/**
 * @brief Determines the lenght of the List
 * 
 * @param list List
 * @return Number of elements on the list
 */
size_t list_size(const List *list);

/**
 * @brief Checks if the List is empty or not
 * 
 * @param list List
 * @return true List is empty
 * @return false List is not empty
 */
bool list_is_empty(const List *list);

/**
 * @brief Checks if the list has order
 * 
 * @param list List
 * @param compare Function to compare the data stored
 * @return true List has order
 * @return false List has no order
 */
bool list_order(const List *list, int (*compare)(const void *, const void *));

/**
 * @brief Adds data to the list
 * If the list has order, it inserts in order, otherwise it adds to the front
 * 
 * @param list List
 * @param data Data to store
 * @param compare Function to compare data
 * @return 0 on sucess, 1 input is NULL, 2 allocation problems
 */
int list_insert(List *list, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Removes the first element that is "equal" to key
 * Mantains the current order
 * 
 * @param list List
 * @param key Item to compare
 * @param compare Function to compare data
 * @return Content stored
 */
void *list_remove(List *list, const void *key, int (*compare)(const void *, const void *));

/**
 * @brief Checks if key exists in the list
 * 
 * @param list Linked List
 * @param key Data to find
 * @param compare Function to compare data
 * @return true Key exists in the list
 * @return false Key does exist in the list
 */
bool list_search(const List *list, const void *key, int (*compare)(const void *, const void *));

/**
 * @brief Creates a linked list identical to list
 * 
 * @param list List
 * @param clone Function to clone data
 * @return Cloned list
 */
List *list_clone(const List *list, void *(*clone)(const void *));

/**
 * @brief Reverses a Linked List
 * 
 * @param list List
 */
void list_reverse(List *list);

/**
 * @brief Determines the minimum value in the list
 * 
 * @param list List
 * @param compare Function to compare data
 * @return Minimal content
 */
void *list_min(const List *list, int (*compare)(const void *, const void *));

/**
 * @brief Determines the maximum value in the list
 * 
 * @param list List
 * @param compare Function to compare data
 * @return Maximal content
 */
void *list_max(const List *list, int (*compare)(const void *, const void *));

/**
 * @brief Takes the first size elements from list
 * 
 * @param list List
 * @param size Number of elements to take
 * @return Remaining elements
 */
List *list_take(List *list, size_t size);

/**
 * @brief Drops the first size elements fromt list
 * 
 * @param list List
 * @param size Number of elements to drop
 * @return Remaining elements
 */
List *list_drop(List *list, size_t size);

/**
 * @brief Concatenates list1 and list2
 * 
 * @param list1 First list
 * @param list2 Second list
 * @return Concatenated list
 * @note Second list becomes empty
 */
List *list_concat(List *list1, List *list2);

/**
 * @brief Merges two SORTED lists
 * 
 * @param list1 First list
 * @param list2 Second list
 * @param compare Function to compare data
 * @note both lists must be sorted
 * @note list2 becomes empty
 * @return Merged List
 */
List *list_merge(List *list1, List *list2, int (*compare)(const void *, const void *));

/**
 * @brief Sorts a linked list
 * 
 * @param list List
 * @param compare Function to compare data
 */
void list_sort(List *list, int (*compare)(const void *, const void *));

/**
 * @brief Shows a linked list
 * 
 * @param list List
 * @param show Function to show the stored data
 * @param fp File pointer
 */
void show_list(const List *list, void (*show)(const void *, FILE *), FILE *fp);

#endif