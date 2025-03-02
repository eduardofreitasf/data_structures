#include "tree.h"
#include <stdlib.h>
#include <time.h>

struct node {
    void *data;
    struct node *left, *right;
};

typedef struct tree {
    size_t size;
    struct node *root;
} Tree;

/**
 * @brief Allocates space for a tree node
 *
 * @param data Data to store
 * @return Pointer to the node
 */
static struct node *create_node(void *data) {
    struct node *new = (struct node *)calloc(1, sizeof(struct node));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->left = new->right = NULL;

    return new;
}

Tree *create_tree(void) {
    Tree *new = (Tree *)calloc(1, sizeof(Tree));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->root = NULL;

    return NULL;
}

/**
 * @brief Frees the allocated space for a tree
 *
 * Assumes destroy is not NULL
 *
 * @param root Root of the tree
 * @param destroy Function to free data
 */
static void clean_nodes(struct node *root, void (*destroy)(void *)) {
    if (root != NULL) {
        // delete data
        if (root->data != NULL)
            destroy(root->data);

        // delete the sub-trees
        clean_nodes(root->left, destroy);
        clean_nodes(root->right, destroy);

        free(root);
    }
}

void destroy_tree(Tree *tree, void (*destroy)(void *)) {
    if (tree != NULL && destroy != NULL) {
        clean_nodes(tree->root, destroy);

        free(tree);
    }
}

int tree_insert(Tree *tree, void *data) {
    if (tree == NULL || data == NULL)
        return 1;

    srand(time(0));

    struct node **temp = &(tree->root);
    if (temp == NULL)
        return 2;

    while (*temp != NULL) {
        // if one sub-tree is NULL, it inserts there
        if ((*temp)->left == NULL)
            temp = &((*temp)->left);
        else if ((*temp)->right == NULL)
            temp = &((*temp)->right);
        else {
            if (rand() % 2 == 0)
                // random number is even, goes to the left
                temp = &((*temp)->left);
            else
                // random number is odd, goes to the right
                temp = &((*temp)->right);
        }
    }

    // attach the new node
    *temp = create_node(data);
    if (*temp == NULL)
        return 2;

    tree->size++;

    return 0;
}

void *tree_remove(Tree *tree, void *data, int (*compare)(const void *, const void *));

/**
 * @brief Traversses the tree with a depth first algorithm
 * 
 * Assumes compare is not NULL
 * 
 * @param root Root of the tree
 * @param compare Function to compare data
 * @return true Key was found
 * @return false Key was not found
 */
static bool depth_first_traversal(const struct node *root, const void *key, int (*compare)(const void *, const void *)) {
    if (root != NULL) {
        if (compare(key, root->data) == 0)
            return true;

        bool temp = depth_first_traversal(root->left, key, compare);
        if (temp == true)
            return true;

        temp = depth_first_traversal(root->right, key, compare);
        if (temp == true)
            return true;
    }

    return false;
}

bool tree_search(const Tree *tree, const void *key, int (*compare)(const void *, const void *)) {
    if (tree == NULL || key == NULL || compare == NULL)
        return false;

    return depth_first_traversal(tree->root, key, compare);
}


size_t tree_size(const Tree *tree) {
    if (tree != NULL)
        return tree->size;
    return 0;
}

bool tree_is_empty(const Tree *tree) {
    return tree != NULL && tree->root == NULL;
}

/**
 * @brief Determines the height of a tree
 *
 * @param root Root of the tree
 * @return Height of the tree
 */
static size_t _tree_height(const struct node *root) {
    if (root == NULL)
        return 0;

    // calculate the height of the sub-trees
    size_t left = _tree_height(root->left);
    size_t right = _tree_height(root->right);

    return 1 + (left > right ? left : right);
}

size_t tree_height(const Tree *tree) {
    if (tree == NULL)
        return 0;

    return _tree_height(tree->root);
}
