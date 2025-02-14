#include "stack.h"
#include <stdlib.h>

struct chain {
    void *data;
    struct chain *next;
};

typedef struct stack {
    size_t size;
    struct chain *top;
} Stack;

struct chain *create_chain(void *data) {
    struct chain *new = (struct chain *)malloc(sizeof(struct chain));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = NULL;

    return new;
}

Stack *stack_create(void) {
    Stack *new = (Stack *)malloc(sizeof(struct stack));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->top = NULL;

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

int stack_push(Stack *stack, void *data) {
    if (stack == NULL || data == NULL)
        return 1;

    struct chain *new_node = create_chain(data);
    if (new_node == NULL)
        return 2;

    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;

    return 0;
}

void *stack_pop(Stack *stack) {
    if (stack == NULL || stack->top == NULL)
        return NULL;

    struct chain *temp = stack->top;
    void *result = temp->data;

    // remove the first node
    stack->top = stack->top->next;
    stack->size--;

    free(temp);

    return result;
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

    stack->size = 0;
    stack->top = NULL;
}

size_t stack_elements(Stack *stack) {
    if (stack == NULL)
        return 0;

    return stack->size;
}

void show_stack(const Stack *stack, void (*show)(const void *, FILE *), FILE *fp) {
    if (stack != NULL && show != NULL && fp != NULL) {
        struct chain *temp = stack->top;

        while (temp != NULL) {
            show(temp->data, fp);
            temp = temp->next;
        }
    }
}