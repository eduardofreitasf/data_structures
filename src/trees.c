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

typedef struct b_tree {
    void *data;
    struct b_tree *right, *left;
} BTree;

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
    while (*temp && compare(btree->data, data) != 0)
        temp =
            compare(btree->data, data) ? &((*temp)->right) : &((*temp)->left);

    if (compare(btree->data, data) == 0)
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
BTree *btree_remove_smallest(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return NULL;

    // go to the left side of the tree
    BTree **temp = &btree;
    while ((*temp)->left)
        temp = &((*temp)->left);

    // remove the node
    BTree *small = *temp;
    temp = &((*temp)->right);
    return small;
}

/**
 * @brief Removes the root of a Binary Search Tree
 *
 * @param btree Binary Search Tree
 * @return void* Data stored on the root (NULL if tree is empty)
 */
void *btree_remove_root(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return NULL;

    BTree *temp = NULL;
    // there is nothing on the right
    if (btree->right == NULL)
        temp = btree->left;
    else {
        // replace the root with the smallest node on the right side (ensures
        // Search property)
        temp = btree_remove_smallest(btree->right);
        temp->left = btree->left;
        temp->right = btree->right;
    }

    // store the data
    void *aux = btree->data;
    // free the allocated space on the node
    free(btree);

    return aux;
}

void *btree_delete(BTree *btree, void *id, int (*compare)(void *, void *)) {
    // tree is empty
    if (btree == NULL)
        return NULL;

    // goes through the tree to find the node
    BTree **temp = &btree;
    while (*temp && compare((*temp)->data, id) != 0)
        temp =
            compare((*temp)->data, id) ? &((*temp)->right) : &((*temp)->left);

    // return the data
    if (compare((*temp)->data, id) == 0)
        return btree_remove_root(*temp);
    else
        return NULL; // does not belong to the tree
}

void *btree_search(BTree *btree, void *id, int (*compare)(void *, void *)) {
    // tree is empty
    if (btree == NULL)
        return NULL;

    // go through the tree, to find the node
    BTree *temp = btree;
    while (temp && compare(temp->data, id) != 0)
        temp = compare(temp->data, id) ? temp->right : temp->left;

    // return the data
    if (compare(temp->data, id) == 0)
        return temp->data;
    else
        return NULL; // does not belong to the tree
}

bool btree_is_empty(BTree *btree) { return btree == NULL; }

unsigned int btree_size(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return 0;

    return btree_size(btree->left) + btree_size(btree->right);
}

void btree_destroy(BTree *btree, void (*free_data)(void *)) {
    if (btree != NULL) {
        // free the object
        free_data(btree->data);

        BTree *l_tmp = btree->left;
        BTree *r_tmp = btree->right;

        // free the structure
        free(btree);
        btree_destroy(l_tmp);
        btree_destroy(r_tmp);
    }
}

unsigned int btree_height(BTree *btree) {
    // tree is empty
    if (btree == NULL)
        return 0;

    unsigned int left = btree_height(btree->left);
    unsigned int right = btree_height(btree->right);

    return 1 + (left > right) ? left : right;
}
