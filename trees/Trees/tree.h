#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Random acess binary tree
 */
typedef struct tree Tree;

/**
 * @brief Creates a Random Tree
 * 
 * @return Pointer to a Tree
 */
Tree *create_tree(void);

/**
 * @brief Frees the allocated space for a Tree
 * 
 * @param tree Random Tree
 * @param destroy Function to destroy data
 */
void destroy_tree(Tree *tree, void (*destroy)(void *));

/**
 * @brief Inserts data in the Tree
 * 
 * @param tree Random Tree
 * @param data Data to store
 * @return 0 on sucess, 1 NULL input, 2 allocation problems
 */
int tree_insert(Tree *tree, void *data);

/**
 * @brief Removes an element from the Tree
 * 
 * @param tree Random tree
 * @param data Data to remove
 * @param compare Function to compare data
 * @return Content stored
 */
void *tree_remove(Tree *tree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Searchs for data in the tree
 * 
 * @param tree Random Tree
 * @param data Data to search for
 * @param compare Function to compare data
 * @return true data was found
 * @return false data was not found
 */
bool tree_search(const Tree *tree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Determines the size of the tree
 * 
 * @param tree Random Tree
 * @return Number of elements on the tree
 */
size_t tree_size(const Tree *tree);

/**
 * @brief Checks if the tree is empty
 * 
 * @param tree Random Tree
 * @return true Tree is empty
 * @return false Tree is not empty
 */
bool tree_is_empty(const Tree *tree);

/**
 * @brief Determines the height of the Tree
 * 
 * @param tree Random Tree
 * @return Height of the Tree
 */
size_t tree_height(const Tree *tree);

/**
 * @brief Shows a Tree
 * 
 * @param tree Random Tree
 * @param show Function to show the data
 * @param fp File pointer
 */
void show_tree(const Tree *tree, void (*show)(const void *, FILE *), FILE *fp);

#endif