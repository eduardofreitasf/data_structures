#ifndef TREES_H
#define TREES_H

typedef struct b_tree BTree;

#include <stdbool.h>

/**
 * @brief Creates a Binary Search Tree, with only one element
 * 
 * @param data Data to be stored
 * @return BTree* New Binary Search Tree
 */
BTree *btree_create(void *data);

/**
 * @brief Inserts data in a Binary Search Tree
 *
 * @param btree Binary Search Tree
 * @param data Data to be inserted
 * @param compare Function to compare elements on the Tree
 * @return true Insertion was sucessfull
 * @return false Insertion was not possible
 */
bool btree_insert(BTree *btree, void *data, int (*compare)(void *, void *));

/**
 * @brief Deletes an element from the Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param id Identifier of the element to remove
 * @param compare Function to compare elements on the Tree
 * @return void* Element that was removed (NULL in case it doesn't exist in the Tree)
 */
void *btree_delete(BTree *btree, void *id, int (*compare)(void *, void *));

/**
 * @brief Searchs for an element in a Binary Search Tree
 * 
 * @param btree Binary Search Tree
 * @param id Identifier of the element to be found
 * @param compare Function to compare elements on the Tree
 * @return void* Element that is being searched (NULL in case it doesn't exist in the Tree)
 */
void *btree_search(BTree *btree, void *id, int (*compare)(void *, void *));

/**
 * @brief Checks if a Binary Search Tree is balanced
 * 
 * @param btree Binary Search tree
 * @return true Is Balanced
 * @return false Not Balanced
 */
bool btree_is_balanced(BTree *btree);

/**
 * @brief Balances a Binary Search Tree
 * 
 * @param btree Binary Search Tree
 */
void btree_balance(BTree *btree);

/**
 * @brief Calculates the number of elements on the Tree
 * 
 * @param btree Binary Search Tree
 * @return unsigned int Number of elements on the Tree
 */
unsigned int btree_size(BTree *btree);

/**
 * @brief Calculates the number of levels on the tree
 *  Assume that the tree is balanced
 * 
 * @param btree Binary Search Tree
 * @return unsigned int Total height
 */
unsigned int btree_height(BTree *btree);

/**
 * @brief Tests if the Tree is empty
 * 
 * @param btree Binary Search Tree
 * @return true Is Empty
 * @return false Not Empty
 */
bool btree_is_empty(BTree *btree);

/**
 * @brief Frees the space alocated by the Tree
 * 
 * @param btree Binary Search Tree
 */
void btree_destroy(BTree* btree);

#endif