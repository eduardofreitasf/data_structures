#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Binary Search Tree
 */
typedef struct binary_tree BSTree;

/**
 * @brief Creates an empty Binary Search Tree
 * 
 * @return pointer to a binary search tree
 */
BSTree *create_btree(void);

/**
 * @brief Frees the allocated space for a Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param destroy Function to free the stored data
 */
void destroy_btree(BSTree *btree, void (*destroy)(void *));

/**
 * @brief Adds data to the tree
 * 
 * @param btree Binary Search Tree
 * @param data Data to insert
 * @param compare Function to compare data
 * @return 0 on sucess, 1 NULL input, 2 allocation problems
 */
int btree_insert(BSTree *btree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Searchs data in the Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param data Data to find
 * @param compare Function to compare data
 * @return true Data was found
 * @return false Data was not found
 */
bool btree_search(const BSTree *btree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Removes data from the Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param data Data to remove
 * @param compare Function to compare data
 * @return Content stored
 * @note The order of the tree remains the same
 */
void *btree_remove(BSTree *btree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Returns the minimum element on the Tree
 * 
 * @param btree Binary Search Tree
 * @return Data stored
 */
void *btree_min(const BSTree *btree);

/**
 * @brief Returns the maximum element on the Tree
 * 
 * @param btree Binary Search Tree
 * @return Data stored
 */
void *btree_max(const BSTree *btree);

/**
 * @brief Returns the number of elements on the tree
 * 
 * @param btree Binary Search Tree
 * @return Number of elements on the tree
 */
size_t btree_size(const BSTree *btree);

/**
 * @brief Checks if the tree is empty
 * 
 * @param btree Binary Search Tree
 * @return true Tree is empty
 * @return false Tree is not empty
 */
bool btree_is_empty(const BSTree *btree);

/**
 * @brief Returns the height of the tree
 * 
 * @param btree Binary Search Tree
 * @return Height of the tree
 */
size_t btree_height(const BSTree *btree);

/**
 * @brief Checks if the tree is balanced
 * 
 * @param btree Binary Search Tree
 * @return true Tree is balanced
 * @return false Tree is not balanced
 */
bool btree_is_balanced(const BSTree *btree);

/**
 * @brief Balances a Binary Search Tree with the DSW algorithm
 * 
 * @param btree Binary Search Tree
 */
void btree_balance(BSTree *btree);

/**
 * @brief Shows a Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param show Function to show data
 * @param fp File pointer
 */
void show_btree(BSTree *btree, void (*show)(const void *, FILE *), FILE *fp);

/**
 * @brief In order traversal of the binary search tree
 * 
 * @param btree Binary Search Tree
 * @return array with the data
 */
void **btree_inorder(const BSTree *btree);

/**
 * @brief Pos order traversal of the binary search tree
 * 
 * @param btree Binary Search Tree
 * @return array with the data
 */
void **btree_posorder(const BSTree *btree);

/**
 * @brief Pos order traversal of the binary search tree
 * 
 * @param btree Binary Search Tree
 * @return array with the data
 */
void **btree_preorder(const BSTree *btree);

#endif