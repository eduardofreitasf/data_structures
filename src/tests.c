/**
 * @file test_trees.c
 * @author Eduardo Fernandes (ef05238@gmail.com)
 * @brief Module for testing Binary Search Trees
 * @version 0.1
 * @date 2024-10-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "tests.h"
#include "lists.h"
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

void show_tree(BTree *tree) {
    printf("Tree: ");
    btree_inorder(tree, &show_int);
    printf("\n");
}

void test_trees(void) {
    srand(time(NULL));

    int value = rand() % 100;
    BTree *tree = NULL;

    // Creating a tree
    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");
    tree = btree_create(create_int(value));
    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");

    show_tree(tree);

    // Testing Insertion
    int limit = rand() % 30;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        bool result = btree_insert(tree, temp, &compare_int);

        if (result) {
            printf("Insertion sucessfull: %d\n", value);
        } else {
            printf("--- Insertion not possible: %d\n", value);
            free(temp);
        }
    }

    show_tree(tree);

    printf("Tree size: %u\n", btree_size(tree));

    printf("Tree is Ordered: %s\n",
           btree_is_ordered(tree, &compare_int) ? "true" : "false");

    printf("Tree height: %u\n", btree_height(tree));

    // for (int i = 0; i < limit; i++) {
    //     value = rand() % 100;
    //     int * temp = create_int(value);
    //     BTree *result = btree_delete(&tree, temp, &compare_int);
    //     free(temp);

    //     if (result) {
    //         free(result);

    //         printf("Deletion sucessfull: %d\n", value);

    //         show_tree(tree);
    //     }
    // }

    show_tree(tree);

    btree_destroy(tree, &free_int);
}

void test_lists(void) {
    srand(time(NULL));

    int value = rand() % 100;
    LList *list = NULL;

    printf("List is empty: %s\n", llist_is_empty(list) ? "true" : "false");
    list = llist_create(create_int(value));
    printf("List is empty: %s\n", llist_is_empty(list) ? "true" : "false");

    llist_show(list, &show_int);

    int limit = rand() % 30;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        llist_insert(&list, temp, &compare_int);

        printf("Inserted: %d\n", value);
    }

    llist_show(list, &show_int);
}