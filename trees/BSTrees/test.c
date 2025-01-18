#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

int main(void) {
    BSTree *new_tree = create_btree();

    

    destroy_btree(new_tree, &destroy_person);

    return 0;
}