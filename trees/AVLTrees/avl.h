#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdbool.h>

typedef struct avl AVLTree;

AVLTree *create_avl(void);
void destroy_avl(AVLTree *tree, void (*destroy)(void *));

int avl_insert(AVLTree *tree, void *data, int (*compare)(const void *, const void *));
void *avl_remove(AVLTree *tree, const void *key, int (*compare)(const void *, const void *));
bool avl_search(const AVLTree *tree, const void *key, int (*compare)(const void *, const void *));


void *avl_min(const AVLTree *tree);
void *avl_max(const AVLTree *tree);

size_t avl_size(const AVLTree *tree);
size_t avl_height(const AVLTree *tree);
bool avl_is_empty(const AVLTree *tree);

void show_avl(const AVLTree *tree, void (*show)(const void *, FILE *), FILE *fp);


#endif