#include "bst.h"
#include <stdlib.h>

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
    struct node *new = (struct node *)malloc(sizeof(void *));
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
    else
        *temp = new;

    return result;
}

int btree_remove(BSTree *btree, void *data, int (*compare)(const void *, const void *));

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

size_t btree_height(const BSTree *btree);
