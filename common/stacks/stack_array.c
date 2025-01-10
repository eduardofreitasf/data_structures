#include "stack.h"
#include <stdlib.h>

typedef struct stack {
    unsigned size, used;
    void **data;
} Stack;

Stack *stack_create(void) {
    Stack *new = malloc(sizeof(struct stack));
    if (new == NULL)
        return NULL;

    // initial size is 1
    void **data = malloc(1 * sizeof(void *));
    if (data == NULL) {
        free(new);
        return NULL;
    }

    *new = (Stack){.size = 1, .used = 0, .data = data};

    return new;
}

void stack_destroy(Stack *stack, void (*destroy)(void *)) {
    if (stack != NULL && destroy != NULL) {
        unsigned i = 0;
        while (i < stack->used) {
            if (stack->data[i] != NULL)
                destroy(stack->data[i]);
            i++;
        }

        free(stack->data);
        free(stack);
    }
}

bool stack_is_empty(Stack *stack) {
    return stack == NULL || stack->used == 0 || stack->size == 0;
}

float stack_load_factor(Stack *stack) {
    return (float)stack->used / (float)stack->size;
}

/*
 * Resizes the array stored by the Stack
 *
 * grow == true -> doubles the size
 * grow == false -> resizes to 2/3
 *
 * Errors: 1 == stack is NULL
 *         2 == realloc() did not work
 *         3 == there are than 2/3 elements on the stack
 */
int stack_resize(Stack *stack, bool grow) {
    if (stack == NULL)
        return 1;

    // double the size
    if (grow == true) {
        stack->size *= 2;
    } else {
        // resize to 2/3
        if (stack_load_factor(stack) < 2.0 / 3.0) {
            stack->size *= 2;
            stack->size /= 3;
        } else {
            return 3;
        }
    }

    stack->data = realloc(stack->data, stack->size * sizeof(void *));
    if (stack->data == NULL)
        return 2;

    return 0;
}

void stack_push(Stack *stack, void *data) {
    if (stack == NULL)
        return;

    // double the size
    if (stack->used == stack->size) {
        int result = stack_resize(stack, true);
        if (result == 2)
            return;
    }

    stack->data[stack->used++] = data;
}

void *stack_pop(Stack *stack) {
    if (stack == NULL || stack->used == 0 || stack->size == 0)
        return NULL;

    // error checking ??
    if (stack_load_factor(stack) < 0.3) {
        stack_resize(stack, false);
    }

    return stack->data[--stack->used];
}

void *stack_top(Stack *stack) {
    if (stack == NULL || stack->used == 0 || stack->size == 0)
        return NULL;

    return stack->data[stack->used - 1];
}

void stack_clear(Stack *stack, void (*destroy)(void *)) {
    if (stack == NULL || destroy == NULL)
        return;

    unsigned i = 0;
    while (i < stack->used)
        destroy(stack->data[i++]);

    stack->used = 0;
}

unsigned stack_elements(Stack *stack) {
    if (stack == NULL)
        return 0;
    return stack->used;
}
