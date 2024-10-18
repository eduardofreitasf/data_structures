/**
 * @file node.c
 * @author Eduardo Fernandes (ef05238@gmail.com)
 * @brief Module that contains an implementation of a node
 * @version 0.1
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "node.h"
#include <assert.h>
#include <stdlib.h>

Node *node_create(void *data) {
    Node *new = (Node *)calloc(1, sizeof(Node));
    assert(new); // is there memory??

    new->data = data;

    return new;
}

D_Node *d_node_create(void *data) {
    D_Node *new = (D_Node *)calloc(1, sizeof(D_Node));
    assert(new); // is there memory ??

    new->data = data;

    return new;
}
