/**
 * @file node.h
 * @author Eduardo Fernandes (ef05238@gmail.com)
 * @brief Module that contains declarations for a Node
 * @version 0.1
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef NODE_H
#define NODE_H

/**
 * @brief Node
 *
 */
typedef struct node {
    //! Stored object
    void *data;
    //! Pointer to the next node
    struct node *next;
} Node;

typedef struct d_node {
    //! Stored object
    void *data;
    //! Pointer to the next node
    struct d_node *next;
    //! Pointer to the previous node
    struct d_node *prev;
} D_Node;

/**
 * @brief Creates a Node with data stored
 *
 * @param data Data to be stored
 * @return Node* Node created
 */
Node *node_create(void *data);

D_Node *d_node_create(void *data);

#endif