#include "stack.h"
#include <stdlib.h>

struct chain {
    void *data;
    struct chain *next;
};

typedef struct stack {
    unsigned size;
    struct chain *top;
} Stack;

struct chain *create_chain(void *data) {
    struct chain *new = (struct chain *)malloc(sizeof(struct chain));
    if (new == NULL)
        return NULL;

    *new = (struct chain){.data = data, .next = NULL};

    return new;
}

Stack *stack_create(void) {
    Stack *new = (Stack *)malloc(sizeof(struct stack));
    if (new == NULL)
        return NULL;

    *new = (Stack){.size = 0, .top = NULL};

    return new;
}

void stack_destroy(Stack *stack, void (*destroy)(void *)) {
    if (stack == NULL || destroy == NULL)
        return;

    struct chain *temp = stack->top, *current = NULL;
    while (temp != NULL) {
        current = temp->next;

        if (temp->data != NULL)
            destroy(temp->data);

        free(temp);
        temp = current;
    }

    free(stack);
}

bool stack_is_empty(Stack *stack) { return stack == NULL || stack->size == 0; }

void stack_push(Stack *stack, void *data) {
    struct chain *new_node = create_chain(data);
    // error handling ??
    if (new_node == NULL || stack == NULL)
        return;

    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

void *stack_pop(Stack *stack) {
    if (stack == NULL || stack->top == NULL)
        return NULL;

    void *temp = stack->top->data;
    stack->top = stack->top->next;

    return temp;
}

void *stack_top(Stack *stack) {
    if (stack == NULL || stack->top == NULL)
        return NULL;

    return stack->top->data;
}

void stack_clear(Stack *stack, void (*destroy)(void *)) {
    if (stack == NULL || destroy == NULL)
        return;

    struct chain *temp = stack->top, *current = NULL;
    while (temp != NULL) {
        current = temp->next;

        if (temp->data != NULL)
            destroy(temp->data);

        free(temp);
        temp = current;
    }

    *stack = (Stack){.size = 0, .top = NULL};
}

unsigned stack_elements(Stack *stack) {
    if (stack == NULL)
        return 0;

    return stack->size;
}
