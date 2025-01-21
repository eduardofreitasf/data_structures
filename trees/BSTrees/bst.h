#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct binary_tree BSTree;

// done and working
BSTree *create_btree(void);
// done and working
void destroy_btree(BSTree *btree, void (*destroy)(void *));

// done and working
int btree_insert(BSTree *btree, void *data, int (*compare)(const void *, const void *));
// done and working
bool btree_search(const BSTree *btree, void *data, int (*compare)(const void *, const void *));
// done and working
void *btree_remove(BSTree *btree, void *data, int (*compare)(const void *, const void *));

// done and working
void *btree_min(const BSTree *btree);
// done and working
void *btree_max(const BSTree *btree);

// done and working
size_t btree_size(const BSTree *btree);
// done and working
bool btree_is_empty(const BSTree *btree);
// done and working
size_t btree_height(const BSTree *btree);

bool btree_is_balanced(const BSTree *btree);
void btree_balance(BSTree *btree);

// done and working
void show_btree(BSTree *btree, void (*show)(const void *, FILE *), FILE *fp);

#endif