#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

#define MAX_VALUE 100
#define STR_SIZE 7

int main(void) {
    srand(time(0));
    
    // FILE *output = fopen("trees.txt", "w");
    FILE *output = stdout;
    void *temp = NULL;
    int value = 0, i = 0, aux = 0;
    int size = 20;

    int array[size], vis[size];
    for (i = 0; i < size; i++) {
        array[i] = i;
        vis[i] = 0;
    }

    BSTree *tree = create_btree();
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    fprintf(output, "------------------- INSERT -------------------\n");
    for (i = 0; i < size;) {
        aux = rand() % size;
        if (vis[aux] == 0) {
            btree_insert(tree, create(array[aux]), &compare_int);
            vis[aux] = 1;
            i++;
        }
    }

    show_btree(tree, &show_int, output);
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    fprintf(output, "------------------- BALANCE -------------------\n");

    btree_balance(tree);
    show_btree(tree, &show_int, output);
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    fprintf(output, "------------------- SEARCH -------------------\n");

    fprintf(output, "searching for %d: '%s'\n", array[3], btree_search(tree, create(array[3]), &compare_int) ? "found" : "not found");
    fprintf(output, "searching for %d: '%s'\n", array[10], btree_search(tree, create(array[10]), &compare_int) ? "found" : "not found");
    value = 50;
    fprintf(output, "searching for %d: '%s'\n", value, btree_search(tree, create(value), &compare_int) ? "found" : "not found");
    fprintf(output, "searching for %d: '%s'\n", array[13], btree_search(tree, create(array[13]), &compare_int) ? "found" : "not found");
    value = 99;
    fprintf(output, "searching for %d: '%s'\n", value, btree_search(tree, create(value), &compare_int) ? "found" : "not found");

    fprintf(output, "------------------- REMOVE -------------------\n");

    temp = btree_remove(tree, create(array[14]), &compare_int);
    if (temp != NULL)
        fprintf(output, "removed %d\n", *(int *)temp);
    else
        fprintf(output, "%d not found\n", array[14]);
    show_btree(tree, &show_int, output);
    
    temp = btree_remove(tree, create(array[3]), &compare_int);
    if (temp != NULL)
        fprintf(output, "removed %d\n", *(int *)temp);
    else
        fprintf(output, "%d not found\n", array[3]);
    temp = btree_remove(tree, create(array[14]), &compare_int);
    if (temp != NULL)
        fprintf(output, "removed %d\n", *(int *)temp);
    else
        fprintf(output, "%d not found\n", array[14]);
    temp = btree_remove(tree, create(array[10]), &compare_int);
    if (temp != NULL)
        fprintf(output, "removed %d\n", *(int *)temp);
    else
        fprintf(output, "%d not found\n", array[10]);

    show_btree(tree, &show_int, output);
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    destroy_btree(tree, &free);

    fprintf(output, "------------------- RANDOM TREE -------------------\n");
    tree = create_btree();

    for (i = 0; i < 30; i++) {
        value = rand() % MAX_VALUE;
        btree_insert(tree, create(value), &compare_int);
    }

    show_btree(tree, &show_int, output);
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    fprintf(output, "------------------- BALANCE -------------------\n");

    btree_balance(tree);
    show_btree(tree, &show_int, output);
    fprintf(output, "tree is empty: '%s'\n", btree_is_empty(tree) ? "true" : "false");
    fprintf(output, "tree size: %ld\n", btree_size(tree));
    fprintf(output, "tree height: %ld\n", btree_height(tree));
    fprintf(output, "tree is balanced: '%s'\n", btree_is_balanced(tree) ? "true" : "false");

    fprintf(output, "------------------- MIN -------------------\n");
    temp = btree_min(tree);
    if (temp != NULL)
        fprintf(output, "min %d\n", *(int *)temp);
    else
        fprintf(output, "tree has no min\n");

    fprintf(output, "------------------- MAX -------------------\n");
    temp = btree_max(tree);
    if (temp != NULL)
        fprintf(output, "max %d\n", *(int *)temp);
    else
        fprintf(output, "tree has no max\n");

    fprintf(output, "------------------- INORDER -------------------\n");
    void **storage = btree_inorder(tree);
    int s = btree_size(tree);
    for (i = 0; i < s; i++)
        show_int(storage[i], output);

    fprintf(output, "\n------------------- POSORDER -------------------\n");
    storage = btree_posorder(tree);
    for (i = 0; i < s; i++)
        show_int(storage[i], output);

    fprintf(output, "\n------------------- PREORDER -------------------\n");
    storage = btree_preorder(tree);
    for (i = 0; i < s; i++)
        show_int(storage[i], output);

    fprintf(output, "\n");
    destroy_btree(tree, &free);

    return 0;
}