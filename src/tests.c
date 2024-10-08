/**
 * @file tests.c
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
void *duplicate_int(void *data) {
    int *new = malloc(sizeof(int));
    assert(new);

    *new = *(int *)data;
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

void lines(void) {
    printf("-----------------------------------------------------\n");
}

void test_trees(void) {
    srand(time(NULL));

    int value = rand() % 100;
    BTree *tree = NULL;

    lines();

    // Creating a tree
    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");
    tree = btree_create(create_int(value));
    printf("Tree is empty: %s\n", btree_is_empty(tree) ? "true" : "false");
    show_tree(tree);

    lines();

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

    lines();

    printf("Tree size: %u\n", btree_size(tree));
    printf("Tree is Ordered: %s\n",
           btree_is_ordered(tree, &compare_int) ? "true" : "false");

    printf("Tree height: %u\n", btree_height(tree));

    lines();

    // Testing Deletion
    show_tree(tree);
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        int *result = btree_delete(&tree, temp, &compare_int);
        free(temp);

        if (result) {
            free(result);
            printf("Deletion sucessfull: %d\n", value);
            show_tree(tree);
        }
    }

    lines();

    // Testing Clone
    BTree *copy = btree_clone(tree, &duplicate_int);
    show_tree(tree);

    printf("Copy -> ");
    show_tree(copy);
    btree_destroy(copy, &free_int);

    lines();

    // Testing Search
    int tb_found = 0;
    printf("Enter a value to search for: ");
    scanf("%d", &tb_found);

    show_tree(tree);
    int *temp_found = create_int(tb_found);
    int *result = btree_search(tree, temp_found, &compare_int, &duplicate_int);

    if (result) {
        printf("Found: %d\n", *result);
        free(result);
    } else {
        printf("Not found.\n");
    }
    free(temp_found);

    lines();

    // Testing Balance
    printf("Tree is balanced: %s\n",
           btree_is_balanced(tree) ? "true" : "false");
    // btree_balance(&tree); // NOT WORKING
    printf("Tree is balanced: %s\n",
           btree_is_balanced(tree) ? "true" : "false");

    lines();

    btree_destroy(tree, &free_int);
}

void test_lists(void) {
    srand(time(NULL));

    // List with order

    puts("\nList with ORDER:");
    int value = rand() % 100;
    LList *list = NULL;

    printf("List is empty: %s\n", llist_is_empty(list) ? "true" : "false");
    list = llist_create(&compare_int, &duplicate_int, &free_int, &show_int);
    llist_insert(list, create_int(50));
    printf("List is empty: %s\n", llist_is_empty(list) ? "true" : "false");

    llist_show(list);

    int limit = rand() % 15;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        llist_insert(list, temp);

        printf("Inserted: %d\n", value);
    }

    llist_show(list);
    printf("List is ordered: %s\n", llist_is_ordered(list) ? "true" : "false");

    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        int *result = llist_delete(list, temp);

        if (result) {
            printf("Deleted: %d\n", value);
            free(result);
        }
        free(temp);
    }

    llist_show(list);

    // List with no order
    puts("\nList with NO ORDER:");

    value = rand() % 100;
    // no order list
    LList *no_list =
        llist_create(&compare_int, &duplicate_int, &free_int, &show_int);
    llist_prepend(no_list, create_int(30));

    llist_show(no_list);
    printf("List is empty: %s\n", llist_is_empty(list) ? "true" : "false");

    limit = rand() % 10;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        llist_append(no_list, temp);

        printf("Appended: %d\n", value);
    }

    llist_show(no_list);
    printf("List is ordered: %s\n",
           llist_is_ordered(no_list) ? "true" : "false");

    limit = rand() % 10;
    for (int i = 0; i < limit; i++) {
        value = rand() % 100;
        int *temp = create_int(value);
        llist_prepend(no_list, temp);

        printf("Prepended: %d\n", value);
    }

    llist_show(no_list);
    putchar('\n');

    int tb_found = 0;
    printf("Insert a value to search for: ");
    scanf("%d", &tb_found);

    int *aux = create_int(tb_found);
    int *result = llist_search(no_list, aux);
    if (result) {
        printf("Found: %d\n", *result);
        free(result);
    } else {
        printf("Not found.\n");
    }
    free(aux);

    printf("Length of the list: %d\n", llist_length(no_list));

    int *min = llist_min(no_list);
    int *max = llist_max(no_list);

    printf("Minimum: %d\n", *min);
    printf("Maximum: %d\n", *max);
    free(min);
    free(max);

    LList *copy = llist_clone(no_list);
    printf("Copy: ");
    llist_show(copy);

    llist_destroy(list);
    llist_destroy(no_list);
    llist_destroy(copy);
}
