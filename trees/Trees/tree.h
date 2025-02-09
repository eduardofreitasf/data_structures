#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct tree Tree;

// done
Tree *create_tree(void);
// done
void destroy_tree(Tree *tree, void (*destroy)(void *));

// done
int tree_insert(Tree *tree, void *data);
void *tree_remove(Tree *tree, void *data, int (*compare)(const void *, const void *));
bool tree_search(const Tree *tree, void *data, int (*compare)(const void *, const void *));

// done
size_t tree_size(const Tree *tree);
// done
bool tree_is_empty(const Tree *tree);
// done
size_t tree_height(const Tree *tree);

void show_tree(const Tree *tree, void (*show)(const void *, FILE *), FILE *fp);

#endif
