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

    BSTree *new_tree = create_btree();
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    fprintf(output, "--- INSERT ---\n");
    for (size_t i = 0; i < 15; i++) {
        btree_insert(new_tree, create_int(rand() % MAX_VALUE), &compare_int);
    }
    show_btree(new_tree, &show_int, output);

    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    fprintf(output, "MIN: ");
    temp = btree_min(new_tree);
    show_int(temp, output);

    fprintf(output, "\nMAX: ");
    temp = btree_max(new_tree);
    show_int(temp, output);
    fprintf(output, "\n");

    fprintf(output, "--- SEARCH ---\n");
    fprintf(output, "searching for: %d\n", *(int *)temp);
    fprintf(output, "found: '%s'\n", btree_search(new_tree, temp, compare_int) ? "true" : "false");

    temp = create_int(rand() % MAX_VALUE);
    fprintf(output, "searching for: %d\n", *(int *)temp);
    fprintf(output, "found: '%s'\n", btree_search(new_tree, temp, compare_int) ? "true" : "false");
    free(temp);
    
    fprintf(output, "--- REMOVE ---\n");
    void *aux = create_int(rand() % MAX_VALUE);
    temp = btree_remove(new_tree, aux, &compare_int);

    if (temp != NULL) {
        fprintf(output, "removed: %d\n", *(int *)temp);
        free(temp);
    } else
        fprintf(output, "%d not found\n", *(int *)aux);
    free(aux);

    show_btree(new_tree, &show_int, output);
    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    destroy_btree(new_tree, &free);

    fprintf(output, "--- Controled tree ---\n");
    new_tree = create_btree();
    btree_insert(new_tree, create_int(50), &compare_int);
    btree_insert(new_tree, create_int(30), &compare_int);
    btree_insert(new_tree, create_int(70), &compare_int);
    btree_insert(new_tree, create_int(60), &compare_int);
    btree_insert(new_tree, create_int(80), &compare_int);
    btree_insert(new_tree, create_int(90), &compare_int);
    btree_insert(new_tree, create_int(20), &compare_int);
    btree_insert(new_tree, create_int(10), &compare_int);
    btree_insert(new_tree, create_int(15), &compare_int);
    btree_insert(new_tree, create_int(25), &compare_int);
    btree_insert(new_tree, create_int(22), &compare_int);
    btree_insert(new_tree, create_int(5), &compare_int);
    btree_insert(new_tree, create_int(2), &compare_int);
    btree_insert(new_tree, create_int(7), &compare_int);
    btree_insert(new_tree, create_int(75), &compare_int);

    show_btree(new_tree, &show_int, output);
    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    fprintf(output, "--- REMOVE ---\n");
    aux = create_int(20);
    temp = btree_remove(new_tree, aux, &compare_int);
    
    if (temp != NULL) {
        fprintf(output, "removed: %d\n", *(int *)temp);
        free(temp);
    } else
        fprintf(output, "%d not found\n", *(int *)aux);
    free(aux);

    show_btree(new_tree, &show_int, output);
    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    fprintf(output, "--- REMOVE ---\n");
    aux = create_int(50);
    temp = btree_remove(new_tree, aux, &compare_int);
    
    if (temp != NULL) {
        fprintf(output, "removed: %d\n", *(int *)temp);
        free(temp);
    } else
        fprintf(output, "%d not found\n", *(int *)aux);
    free(aux);

    show_btree(new_tree, &show_int, output);
    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");

    fprintf(output, "--- REMOVE ---\n");
    aux = create_int(90);
    temp = btree_remove(new_tree, aux, &compare_int);
    
    if (temp != NULL) {
        fprintf(output, "removed: %d\n", *(int *)temp);
        free(temp);
    } else
        fprintf(output, "%d not found\n", *(int *)aux);
    free(aux);

    show_btree(new_tree, &show_int, output);
    fprintf(output, "Size: %ld\n", btree_size(new_tree));
    fprintf(output, "Height: %ld\n", btree_height(new_tree));
    fprintf(output, "Is empty: '%s'\n", btree_is_empty(new_tree) ? "true" : "false");



    destroy_btree(new_tree, &free);

    return 0;
}