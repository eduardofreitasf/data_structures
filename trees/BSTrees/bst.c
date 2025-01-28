#include "bst.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {
    void *data;
    struct node *left, *right;
};

typedef struct binary_tree {
    size_t size;
    struct node *root;
} BSTree;

/**
 * @brief Allocates space for a tree node
 * 
 * @param data Data to store
 * @return struct node* Allocated Node (NULL on allocation error)
 */
static struct node *create_node(void *data) {
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->left = new->right = NULL;

    return new;
}

BSTree *create_btree(void) {
    BSTree *new = (BSTree *)malloc(sizeof(BSTree));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->root = NULL;    

    return new;
}

/**
 * @brief Frees the allocated space for all the node on the tree
 * 
 * This function assumes destroy is not NULL
 * 
 * @param root Binary Search Tree
 * @param destroy Function to free the content of each node
 */
static void clean_nodes(struct node *root, void (*destroy)(void *)) {
    if (root == NULL)
        return;

    if (root->data != NULL)
        destroy(root->data);

    clean_nodes(root->left, destroy);
    clean_nodes(root->right, destroy);

    free(root);
}

void destroy_btree(BSTree *btree, void (*destroy)(void *)) {
    if (btree == NULL || destroy == NULL)
        return;

    clean_nodes(btree->root, destroy);
    free(btree);
}

int btree_insert(BSTree *btree, void *data, int (*compare)(const void *, const void *)) {
    if (btree == NULL || compare == NULL)
        return 1;

    struct node **temp = &(btree->root);
    while (*temp != NULL) {
        if (compare((*temp)->data, data) < 0)
            temp = &((*temp)->right);
        else
            temp = &((*temp)->left);
    }

    struct node *new = create_node(data);
    int result = 0;
    if (new == NULL)
        result = 2;
    else {
        *temp = new;
        btree->size++;
    }

    return result;
}

/**
 * @brief Removes the biggest element from a binary search tree
 * 
 * Assumes root and compare are not NULL
 * 
 * @param root Root of the tree
 * @param compare Function to compare elements
 * @return struct node* Biggest node
 */
static struct node *remove_biggest(struct node **root) {
    while ((*root)->right != NULL)
        root = &((*root)->right);

    struct node *result = *root;
    *root = NULL;

    return result;
}

/**
 * @brief Removes the root of a tree and replaces it with the largest node from the left subtree
 * 
 * Assumes root and compare are not NULL
 * 
 * @param root Root of the tree
 * @param compare Function to compare elements
 * @return void* Data stored on the root
 */
static void *remove_root(struct node **root) {
    void *result = (*root)->data;
    struct node *temp = NULL;
    struct node *left = (*root)->left;
    struct node *right = (*root)->right;

    if (left == NULL) {
        temp = right;
        // free the node
        free(*root);
        // replace the node
        *root = temp;
    } else {
        // remove the biggest on the left sub-tree
        temp = remove_biggest(&left);

        // free the node
        free(*root);
        // replace the node
        *root = temp;
        // atach the sub-trees
        if (temp->left == NULL)
            (*root)->left = left;
        (*root)->right = right;
    }

    return result;
}

void *btree_remove(BSTree *btree, void *data, int (*compare)(const void *, const void *)) {
    if (btree == NULL || compare == NULL || data == NULL)
        return NULL;

    struct node **temp = &(btree->root);
    // find the node
    while (*temp != NULL && compare((*temp)->data, data) != 0) {
        if (compare((*temp)->data, data) < 0)
            temp = &((*temp)->right);
        else
            temp = &((*temp)->left);
    }

    void *result = NULL;
    // found data
    if (*temp != NULL) {
        result = remove_root(temp);
        btree->size--;
    }

    return result;
}

bool btree_search(const BSTree *btree, void *data, int (*compare)(const void *, const void *)) {
    if (btree == NULL || compare == NULL)
        return false;

    struct node *temp = btree->root;
    while (temp != NULL) {
        if (compare(temp->data, data) == 0)
            return true;
        if (compare(temp->data, data) > 0)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return false;
}

void *btree_min(const BSTree *btree) {
    if (btree == NULL || btree->root == NULL)
        return NULL;

    // go to the left node
    struct node *temp = btree->root;
    while (temp->left != NULL)
        temp = temp->left;

    return temp->data;
}

void *btree_max(const BSTree *btree) {
    if (btree == NULL || btree->root == NULL)
        return NULL;

    // go to the right node
    struct node *temp = btree->root;
    while (temp->right != NULL)
        temp = temp->right;

    return temp->data;
}

size_t btree_size(const BSTree *btree) {
    return btree == NULL ? 0 : btree->size;
}

bool btree_is_empty(const BSTree *btree) {
    return btree == NULL || btree->root == NULL || btree->size == 0;
}

/**
 * @brief Calculates the height of a binary tree
 * 
 * @param root Root of the tree
 * @return size_t Height of the tree
 */
static size_t _btree_height(const struct node *root) {
    if (root == NULL)
        return 0;

    size_t left = _btree_height(root->left);
    size_t right = _btree_height(root->right);

    return 1 + (left > right ? left : right);
}

size_t btree_height(const BSTree *btree) {
    if (btree == NULL)
        return 0;

    return _btree_height(btree->root);
}

bool btree_is_balanced(const BSTree *btree) {
    if (btree != NULL) {
        if (btree->size == 0)
            return true;

        size_t ideal_height = (size_t) log2(btree->size) + 1;
        size_t height = btree_height(btree);

        return (height - ideal_height) < 2;
    }
    return false;
}

/**
 * @brief Rotates a binary tree to the left
 * 
 * Assumes root is not NULL, and the right sub tree is not NULL
 * 
 * @param root Root of the tree
 */
static void rotate_left(struct node **root) {
    struct node *right = (*root)->right;

    (*root)->right = right->left;
    right->left = *root;
    *root = right;
}

/**
 * @brief Rotates a binary tree to the right
 * 
 * Assumes root is not NULL, and the left sub tree is not NULL
 * 
 * @param root Root of the tree
 */
static void rotate_right(struct node **root) {
    struct node *left = (*root)->left;

    (*root)->left = left->right;
    left->right = *root;
    *root = left;
}

/**
 * @brief Transforms a binary search tree in a spine (each node has no left sub-tree)
 * 
 * Assumes root is not NULL
 * 
 * @param root Root of the tree
 */
static void build_spine(struct node **root) {
    while (*root != NULL) {
        while ((*root)->left != NULL)
            rotate_right(root);

        root = &((*root)->right);
    }
}

/**
 * @brief 
 * 
 * @param root 
 * @param n_memb 
 */
static void balance_spine(struct node **root, size_t n_memb) {
    size_t height = log2(n_memb);
    size_t total = pow(2, height) - 1;
    // number of nodes on the last level
    size_t bottom = n_memb - total;

    struct node **temp = root;
    // rotate the bottom nodes
    while (bottom > 0 && *temp != NULL && (*temp)->right != NULL) {
        rotate_left(temp);
        temp = &((*temp)->right);
        bottom--;
    }

    n_memb -= n_memb - total;
    // rotate the odd nodes to the left
    while (n_memb > 0) {
        n_memb /= 2;
        total = n_memb;
        temp = root;

        while (total > 0 && (*temp)->right != NULL) {
            rotate_left(temp);
            total--;
            temp = &((*temp)->right);
        }
    }
}

void btree_balance(BSTree *btree) {
    if (btree->root != NULL) {
        build_spine(&(btree->root));
        balance_spine(&(btree->root), btree->size);
    }
}

/**
 * @brief Traversses the binary search tree, by the breath first algorithm
 * Fills the storage array with the nodes in the corresponding order
 * 
 * Assumes root and storage are not NULL
 * 
 * @param root Root of the tree
 * @param storage Array to store the nodes
 */
static void breath_first_traversal(struct node *root, struct node *storage[], size_t size) {
    size_t start = 0, end = 0;
    // enqueue
    storage[end++] = root;

    while (start < end && end < size) {
        // dequeue
        root = storage[start++];
        // NULL is an empty node
        if (root != NULL) {
            // enqueue
            storage[end++] = root->left;
            storage[end++] = root->right;
        } else if (end + 2 < size)
            end += 2;
    }
}

void show_btree(BSTree *btree, void (*show)(const void *, FILE *), FILE *fp) {
    if (btree == NULL || show == NULL || fp == NULL || btree->root == NULL || btree->size == 0)
        return;

    size_t total = (size_t) pow(2, btree_height(btree)) - 1;

    struct node *storage[total];
    size_t iterate = 0;
    for (; iterate < total; iterate++) {
        storage[iterate] = NULL;
    }

    breath_first_traversal(btree->root, storage, total);

    size_t level = 1, count = 0, space = 0;
    for (iterate = 0; iterate < total; iterate++) {
        if (count == level) {
            fprintf(fp, "\n");
            level *= 2;
            count = 0;
            space = 0;
        }
        if (space == 2) {
            fprintf(fp, " ");
            space = 0;
        }
        space++;
        count++;

        if (storage[iterate] != NULL)
            show(storage[iterate]->data, fp);
        else
            fprintf(fp, "X ");
    }

    fprintf(fp, "\n");
}
