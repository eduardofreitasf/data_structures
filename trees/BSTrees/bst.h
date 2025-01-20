#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct binary_tree BSTree;

BSTree *create_btree(void);
void destroy_btree(BSTree *btree, void (*destroy)(void *));

int btree_insert(BSTree *btree, void *data, int (*compare)(const void *, const void *));
int btree_remove(BSTree *btree, void *data, int (*compare)(const void *, const void *));
bool btree_search(const BSTree *btree, void *data, int (*compare)(const void *, const void *));

void *btree_min(const BSTree *btree);
void *btree_max(const BSTree *btree);

size_t btree_size(const BSTree *btree);
bool btree_is_empty(const BSTree *btree);
size_t btree_height(const BSTree *btree);

bool btree_is_balanced(const BSTree *btree);
void btree_balance(BSTree *btree);


void show_btree(BSTree *btree, void (*show)(const void *, FILE *), FILE *fp);

#endif