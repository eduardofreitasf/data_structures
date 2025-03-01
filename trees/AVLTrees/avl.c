#include "avl.h"
#include <stdlib.h>

#define BALANCED 0
#define LEFT (-1)
#define RIGHT 1

struct node {
    void *data;
    struct node *left, *right;
    short int balance;
};

typedef struct avl {
    size_t size;
    struct node *root;
} AVLTree;

AVLTree *create_avl(void) {
    AVLTree *new = (AVLTree *)malloc(sizeof(AVLTree));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->root = NULL;

    return new;
}

/**
 * @brief Allocates space for Tree node
 *
 * @param data data to store
 * @return pointer to the node
 */
static struct node *create_node(void *data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;

    new_node->data = data;
    new_node->balance = BALANCED;
    new_node->left = new_node->right = NULL;

    return new_node;
}

/**
 * @brief Frees the allocated memory for a Tree
 *
 * Assumes destroy is not NULL
 *
 * @param root root of the tree
 * @param destroy function to free the stored data
 */
static void clean_nodes(struct node *root, void (*destroy)(void *)) {
    if (root != NULL) {
        if (root->data != NULL)
            destroy(root->data);

        clean_nodes(root->left, destroy);
        clean_nodes(root->right, destroy);

        free(root);
    }
}

void destroy_avl(AVLTree *tree, void (*destroy)(void *)) {
    if (tree != NULL && destroy != NULL)
        clean_nodes(tree->root, destroy);
}

/**
 * @brief Rotates an AVL Tree to the left
 *
 * Assumes root is not NULL, and there is atleast 3 elements on the tree
 *
 * @param root root of the tree
 */
static void rotate_left(struct node **root) {
    struct node *right = (*root)->right;
    (*root)->right = right->left;
    *root = right;
}

/**
 * @brief Rotates an AVL Tree to the right
 *
 * Assumes root is not NULL, and there is atleast 3 elements on the tree
 *
 * @param root root of the tree
 */
static void rotate_right(struct node **root) {
    struct node *left = (*root)->left;
    (*root)->left = left->right;
    *root = left;
}

/**
 * @brief Fix's the right sub-tree
 *
 * Assumes root and root->right are not NULL
 *
 * @param root root of the tree
 * @return pointer to the fixed tree
 */
static struct node *fix_right(struct node *root) {
    struct node *temp = root->right;

    // right sub-tree is heavier on the right
    if (temp->balance == RIGHT) {
        root->balance = temp->balance = BALANCED;
        rotate_left(&root);
    } else if (temp->balance == LEFT) {
        // right sub-tree is heavier on the left

        // adjust the balance factors
        switch (temp->left->balance) {
            case BALANCED:
                root->balance = temp->balance = BALANCED;
                break;
            case RIGHT:
                root->balance = LEFT;
                temp->balance = BALANCED;
                break;
            case LEFT:
                root->balance = BALANCED;
                temp->balance = RIGHT;
                break;
            default:
                break;
        }

        // right sub-tree is heavier on the left
        rotate_right(&(temp));
        rotate_left(&root);

        root->balance = BALANCED;
    }

    return root;
}

/**
 * @brief Fix's the left sub-tree
 *
 * Assumes root and root->left are not NULL
 *
 * @param root root of the tree
 * @return pointer to the fixed tree
 */
static struct node *fix_left(struct node *root) {
    struct node *temp = root->left;

    // left sub-tree is heavier on the left
    if (temp->balance == LEFT) {
        root->balance = temp->balance = BALANCED;
        rotate_right(&root);
    } else if (temp->balance == RIGHT) {
        // left sub-tree is heavier on the right

        // adjust the balance factors
        switch (temp->right->balance) {
            case BALANCED:
                root->balance = temp->balance = BALANCED;
                break;
            case RIGHT:
                root->balance = BALANCED;
                temp->balance = LEFT;
                break;
            case LEFT:
                root->balance = RIGHT;
                temp->balance = BALANCED;
                break;
            default:
                break;
        }

        // left sub-tree is heavier on the right
        rotate_left(&(root->left));
        rotate_right(&root);

        root->balance = BALANCED;
    }

    return root;
}

/**
 * @brief Adds data to the tree and balances it if necessary
 *
 * Assumes input is not NULL
 *
 * @param root pointer to the root of the tree
 * @param data data to store
 * @param compare function to compare data
 * @param growth flag to indicate whether the height of the tree changed
 * @return pointer to the root of the tree
 */
static struct node *avl_insert_rec(struct node *root, void *data,
                                   int (*compare)(const void *, const void *),
                                   bool *growth) {
    // bottom of the tree
    if (root == NULL) {
        struct node *new_node = create_node(data);
        if (new_node == NULL) {
            *growth = false;
            return NULL;
        }
        *growth = true;
    } else if (compare(root->data, data) < 0) {
        root->right = avl_insert_rec(root->right, data, compare, growth);
        // right tree grew
        if (*growth == true) {
            // calculate the new balance factor
            switch (root->balance) {
                case BALANCED:
                    root->balance = RIGHT;
                    break;
                case RIGHT:
                    // right side has more elements
                    root = fix_right(root);
                    *growth = false;
                    break;
                case LEFT:
                    root->balance = BALANCED;
                    break;
                default:
                    break;
            }
        }
    } else if (compare(root->data, data) > 0) {
        root->left = avl_insert_rec(root->left, data, compare, growth);
        // left tree grew
        if (*growth == true) {
            // calculate the new balance factor
            switch (root->balance) {
                case BALANCED:
                    root->balance = LEFT;
                    break;
                case RIGHT:
                    root->balance = BALANCED;
                    break;
                case LEFT:
                    // left side has more elements
                    root = fix_left(root);
                    *growth = false;
                    break;
                default:
                    break;
            }
        }
    } // if data already exists, nothing is done

    return root;
}

int avl_insert(AVLTree *tree, void *data, int (*compare)(const void *, const void *)) {
    if (tree != NULL && compare != NULL) {
        bool growth = false;
        tree->root = avl_insert_rec(tree->root, data, compare, &growth);

        return 0;
    }

    return 1;
}

/**
 * @brief 
 * 
 * @param root 
 * @return struct node* 
 */
static struct node *remove_smallest(struct node **root) {
    return NULL;
}

/**
 * @brief Removes the root of a Tree, replacing it by the smallest on the right
 * 
 * @param root root of the tree
 * @return stored data
 */
static void *remove_root(struct node **root) {
    void *result = (*root)->data;
    struct node *temp = NULL;
    struct node *left = (*root)->left;
    struct node *right = (*root)->right;

    if (left == NULL)
        temp = right;
    else {
        // remove the smallest on the right sub-tree
        temp = remove_smallest(&left);

        // atach the sub-trees
        temp->left = left;
        temp->right = right;
    }

    free(*root);
    // replace the node
    *root = temp;

    return result;
}

void *avl_remove(AVLTree *tree, const void *key, int (*compare)(const void *, const void *)) {
    if (tree == NULL || key == NULL || compare == NULL)
        return NULL;
}

bool avl_search(const AVLTree *tree, const void *key,
                int (*compare)(const void *, const void *)) {
    if (tree == NULL || key == NULL || compare == NULL)
        return false;

    bool result = false;
    struct node *temp = tree->root;

    // go either left or right
    while (temp != NULL && compare(temp->data, key) != 0) {
        if (compare(temp->data, key) < 0)
            temp = temp->right;
        else
            temp = temp->left;
    }

    // found the key
    if (temp != NULL)
        result = true;

    return result;
}

void *avl_min(const AVLTree *tree) {
    if (tree == NULL || tree->root == NULL)
        return NULL;

    struct node *temp = tree->root;
    // go to the bottom left node
    while (temp->left != NULL)
        temp = temp->left;

    return temp->data;
}

void *avl_max(const AVLTree *tree) {
    if (tree == NULL || tree->root == NULL)
        return NULL;

    struct node *temp = tree->root;
    // go to the bottom right node
    while (temp->right != NULL)
        temp = temp->right;

    return temp->data;
}

size_t avl_size(const AVLTree *tree) {
    if (tree != NULL)
        return tree->size;
    return 0;
}

size_t avl_height(const AVLTree *tree) {
    if (tree == NULL)
        return 0;

    size_t height = 0;
    struct node *temp = tree->root;
    // follow the longest path
    while (temp != NULL) {
        if (temp->balance == RIGHT)
            temp = temp->right;
        else
            temp = temp->left;

        height++;
    }

    return height;
}

bool avl_is_empty(const AVLTree *tree) {
    return tree == NULL || tree->root == NULL || tree->size == 0;
}

void show_avl(const AVLTree *tree, void (*show)(const void *, FILE *),
              FILE *fp);
