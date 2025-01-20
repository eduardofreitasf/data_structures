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
    char *temp = NULL;

    BSTree *new_tree = create_btree();

    for (size_t i = 0; i < 10; i++) {
        btree_insert(new_tree, create_int(rand() % MAX_VALUE), &compare_int);
    }

    show_btree(new_tree, &show_int, output);

    destroy_btree(new_tree, &free);

    return 0;
}