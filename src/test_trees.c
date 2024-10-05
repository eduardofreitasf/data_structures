
#include "test_trees.h"
#include "trees.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// if x is bigger, returns positive value
// if x is smaller, returns negative value
// if equal, returns zero
int compare_int(void *x, void *y) { return *(int *)x - *(int *)y; }

// frees the allocated space of an int
void free_int(void *data) { free(data); }

// allocates space for an int, and copys the value of data into new
int *duplicate_int(int *data) {
    int *new = malloc(sizeof(int));
    assert(new);

    *new = *data;
    return new;
}

// allocates space for an int
int *create_int(int value) {
    int *new = (int *)malloc(sizeof(int));
    assert(new);

    *new = value;
    return new;
}

// shows the value stored in an integer pointer
void show_int(void *value) { printf("%d ", *(int *)value); }

void test_trees(void) {
    srand(time(NULL));

    int value = rand() % 100;
    BTree *tree = NULL;

    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");
    tree = btree_create(create_int(value));
    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");

    printf("Tree: ");
    btree_inorder(tree, &show_int);
    printf("\n");

    int limit = rand() % 30;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        bool result = btree_insert(tree, create_int(value), &compare_int);

        result ? printf("Insertion sucessfull: %d\n", value) : printf("Insertion not possible: %d\n", value);
    }

    printf("Tree: ");
    btree_inorder(tree, &show_int);
    printf("\n");

    printf("Tree is Ordered: %s\n", btree_is_ordered(tree, &compare_int) ? "true" : "false");


    btree_destroy(tree, &free_int);

}