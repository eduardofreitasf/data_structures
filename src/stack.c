
#include "stack.h"
#include "node.h"
#include <assert.h>
#include <stdlib.h>

typedef struct stack {
    //! Stack size
    unsigned int size;
    //! Stack top
    Node *top;
    //! Function to duplicate elements
    void *(*duplicate)(void *);
    //! Function to free elements
    void (*free_data)(void *);
    //! Function to show elements
    void (*show_data)(void *);
} Stack;

Stack *stack_create(void *(*duplicate)(void *), void (*free_data)(void *),
                    void (*show_data)(void *)) {
    Stack *new = (Stack *)calloc(1, sizeof(Stack));
    assert(new); // is there memory ??

    // attribute the functions
    new->duplicate = duplicate;
    new->free_data = free_data;
    new->show_data = show_data;

    return new;
}

void push(Stack *stack, void *data) {
    // new node
    Node *new = node_create(data);

    // replace the top
    new->next = stack->top;
    stack->top = new;

    stack->size++;
}

void *pop(Stack *stack) {
    if (stack->top == NULL)
        return NULL;

    Node *temp = stack->top;
    // update the top node
    stack->top = stack->top->next;
    stack->size--;

    void *dup = stack->duplicate(temp->data);
    // free the space of the node
    stack->free_data(temp->data);
    free(temp);

    return dup;
}

void *top(Stack *stack) {
    if (stack->top == NULL)
        return NULL;

    return stack->duplicate(stack->top->data);
}

void show_stack(Stack *stack) {
    Node *temp = stack->top;
    while (temp) {
        stack->show_data(temp->data);
        temp = temp->next;
    }
}

void free_stack(Stack *stack) {
    Node *temp = NULL;
    while (temp) {
        stack->free_data(stack->top->data);
        temp = stack->top->next;
        free(stack->top);
        stack->top = temp;
    }

    free(stack->top);
    free(stack);
}
