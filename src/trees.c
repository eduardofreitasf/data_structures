/**
 * @file trees.c
 * @author Eduardo Fernandes (ef05238@gmail.com)
 * @brief Module containing Binary Search Trees operations
 * @version 0.1
 * @date 2024-10-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "trees.h"
#include <assert.h>
#include <stdlib.h>

// Data Structures

/**
 * @brief Data Structure of a Binary Tree
 *
 */
typedef struct b_tree {
    void *data;           // Data to store
    struct b_tree *left;  // pointer to left node
    struct b_tree *right; // pointer to right node
} BTree;

// Functions

BTree *btree_create(void *data) {
    BTree *new_tree = (BTree *)calloc(1, sizeof(BTree));
    assert(new_tree); // is there memory??

    new_tree->data = data;

    return new_tree;
}

bool btree_insert(BTree *btree, void *data, int (*compare)(void *, void *)) {
    // tree is empty
    if (btree == NULL)
        return false;

    // go through the tree to find the place to insert (or the element)
    BTree **temp = &btree;
    while (*temp && compare((*temp)->data, data) != 0) {
        temp = compare((*temp)->data, data) > 0 ? &((*temp)->left)
                                                : &((*temp)->right);
    }

    if (*temp)
        return false; // already exists in the tree

    // generate a new node
    BTree *new = btree_create(data);
    *temp = new;

    return true; // insertion was sucessfull
}

/**
 * @brief Removes the smallest node from the Binary Search Tree
 *
 * @param btree Binary Search Tree
 * @return BTree* Smallest node
 */
BTree *btree_remove_smallest(BTree **btree) {
    // tree is empty
    if (*btree == NULL)
        return NULL;

    // go to the left side of the tree
    while ((*btree)->left)
        btree = &((*btree)->left);

    // remove the node
    BTree *small = *btree;
    *btree = (*btree)->right;
    return small;
}

/**
 * @brief Removes the root of a Binary Search Tree
 *
 * @param btree Binary Search Tree
 * @return void* Data stored on the root (NULL if tree is empty)
 */
void *btree_remove_root(BTree **btree) {
    // tree is empty
    if (*btree == NULL)
        return NULL;

    BTree *temp = NULL;
    // there is nothing on the right
    if ((*btree)->right == NULL)
        temp = (*btree)->left;
    else {
        // replace the root with the smallest node on the right side (ensures
        // Search property)
        temp = btree_remove_smallest(&((*btree)->right));
        temp->left = (*btree)->left;
        temp->right = (*btree)->right;
    }

    // store the data
    void *aux = (*btree)->data;
    // free the allocated space on the node
    free(*btree);
    *btree = temp;

    return aux;
}

void *btree_delete(BTree **btree, void *id, int (*compare)(void *, void *)) {
    // tree is empty
    if (*btree == NULL)
        return NULL;

    // goes through the tree to find the node
    // BTree **temp = btree;
    while (*btree && compare((*btree)->data, id) != 0)
        btree = compare((*btree)->data, id) > 0 ? &((*btree)->left)
                                                : &((*btree)->right);

    // return the data
    if (*btree)
        return btree_remove_root(btree);
    else
        return NULL; // does not belong to the tree
}

void *btree_search(BTree *btree, void *id, int (*compare)(void *, void *),
                   void *(*duplicate)(void *)) {
    // tree is empty
    if (btree == NULL)
        return NULL;

    // go through the tree, to find the node
    BTree *temp = btree;
    while (temp && compare(temp->data, id) != 0)
        temp = compare(temp->data, id) > 0 ? temp->left : temp->right;

    // return the data
    if (temp)
        return duplicate(temp->data);
    else
        return NULL; // does not belong to the tree
}

bool btree_is_empty(BTree *btree) { return btree == NULL; }

unsigned int btree_size(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return 0;

    return 1 + btree_size(btree->left) + btree_size(btree->right);
}

void btree_destroy(BTree *btree, void (*free_data)(void *)) {
    if (btree != NULL) {
        // free the object
        free_data(btree->data);

        BTree *l_tmp = btree->left;
        BTree *r_tmp = btree->right;

        // free the structure
        free(btree);
        btree_destroy(l_tmp, free_data);
        btree_destroy(r_tmp, free_data);
    }
}

unsigned int btree_height(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return 0;

    unsigned int left = btree_height(btree->left);
    unsigned int right = btree_height(btree->right);

    return 1 + ((left > right) ? left : right);
}

/**
 * @brief Tests if a the values in a Binary Search Tree are bigger than id
 *
 * @param btree Binary Search Tree
 * @param id Object
 * @param compare Positive if first argument is greater, zero if equal
 * @return true Is bigger
 * @return false Not bigger
 */
bool btree_bigger(BTree *btree, void *id, int (*compare)(void *, void *)) {
    if (btree == NULL)
        return true;

    return compare(id, btree->data) < 0 &&
           btree_bigger(btree->left, id, compare) &&
           btree_bigger(btree->right, id, compare);
}

/**
 * @brief Tests if the values in a Binary Search Tree are smaller than id
 *
 * @param btree Binary Search Tree
 * @param id Object
 * @param compare Positive if first argument is greater, zero if equal
 * @return true Is smaller
 * @return false Not smaller
 */
bool btree_smaller(BTree *btree, void *id, int (*compare)(void *, void *)) {
    if (btree == NULL)
        return true;

    return compare(id, btree->data) > 0 &&
           btree_smaller(btree->left, id, compare) &&
           btree_smaller(btree->right, id, compare);
}

bool btree_is_ordered(BTree *btree, int (*compare)(void *, void *)) {
    if (btree == NULL)
        return true;

    return btree_bigger(btree->right, btree->data, compare) &&
           btree_smaller(btree->left, btree->data, compare) &&
           btree_is_ordered(btree->right, compare) &&
           btree_is_ordered(btree->left, compare);
}

BTree *btree_clone(BTree *btree, void *(*duplicate)(void *)) {
    BTree *new = NULL;
    if (btree != NULL) {
        // duplicate the data
        void *new_data = duplicate(btree->data);
        // create node
        new = btree_create(new_data);

        // clone left and right side
        new->left = btree_clone(btree->left, duplicate);
        new->right = btree_clone(btree->right, duplicate);
    }

    return new;
}

/**
 * @brief Transforms a Binary Search Tree into a Spine shape Tree
 *
 * @param btree Binary Tree
 * @param last Binary Tree
 * @return int Number of nodes
 */
int btree_build_spine_aux(BTree **btree, BTree **last) {
    if (*btree == NULL)
        return 0;

    // Recursively build spine from the left subtree
    int count_l = btree_build_spine_aux(&((*btree)->left), last);

    // Attach the current node to the last processed node in the spine
    if (*last != NULL) {
        (*last)->right = *btree;
    }

    // Set the left pointer of the current node to NULL (since it's a spine)
    (*btree)->left = NULL;

    // Update 'last' to point to the current node
    *last = *btree;

    // Temporarily store the right child of the current node
    BTree *right = (*btree)->right;

    // Recursively build spine from the right subtree
    int count_r = btree_build_spine_aux(&right, last);

    // Reattach the processed right subtree to the current node
    (*btree)->right = right;

    // Return the total number of nodes processed (left + current + right)
    return 1 + count_l + count_r;
}

/**
 * @brief Transforms a Binary Search Tree into a Spine shape Tree
 *
 * @param btree Binary Search Tree
 * @return int Number of nodes on the Tree
 */
int btree_build_spine(BTree **btree) {
    BTree *auxiliar = NULL;

    return btree_build_spine_aux(btree, &auxiliar);
}

/**
 * @brief Balances a Spine shape Tree
 *
 * @param btree Spine shape tree
 * @param n_nodes Number of nodes on the tree
 * @return BTree* Balanced Binary Search Tree
 */
BTree *btree_balance_spine(BTree **btree, int n_nodes) {
    if (n_nodes <= 0 || *btree == NULL)
        return NULL;

    // Calculate the size of the left subtree
    int left_size = (n_nodes - 1) / 2;

    // Recursively balance the left subtree
    BTree *left = btree_balance_spine(btree, left_size);

    // The current node will be the new root
    BTree *current = *btree;

    // Move the pointer to the next node in the spine
    *btree = (*btree)->right;

    // Attach the balanced left subtree to the current node
    current->left = left;

    // Recursively balance the right subtree with remaining nodes
    current->right = btree_balance_spine(btree, n_nodes - left_size - 1);

    return current;
}

void btree_balance(BTree **btree) {
    if (*btree != NULL) {
        // turn tree into spine
        int nodes = btree_build_spine(btree);

        // balance the spine
        *btree = btree_balance_spine(btree, nodes);
    }
}

bool btree_is_balanced(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return true;

    // calculate height on both sides
    unsigned int l_height = btree_height(btree->left);
    unsigned int r_height = btree_height(btree->right);

    // difference is above 1, not balanced
    if ((l_height > r_height && l_height - r_height > 1) ||
        (r_height > l_height && r_height - l_height > 1))
        return false;

    // check the left and right side
    return btree_is_balanced(btree->left) && btree_is_balanced(btree->right);
}

void btree_inorder(BTree *btree, void (*show)(void *)) {
    if (btree != NULL) {
        btree_inorder(btree->left, show);
        show(btree->data);
        btree_inorder(btree->right, show);
    }
}

void btree_preorder(BTree *btree, void (*show)(void *)) {
    if (btree != NULL) {
        show(btree->data);
        btree_preorder(btree->left, show);
        btree_preorder(btree->right, show);
    }
}

void btree_posorder(BTree *btree, void (*show)(void *)) {
    if (btree != NULL) {
        btree_posorder(btree->left, show);
        btree_posorder(btree->right, show);
        show(btree->data);
    }
}
