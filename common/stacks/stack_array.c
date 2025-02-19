#include "stack.h"
#include <stdlib.h>

#define GROW 1
#define SHRINK (-1)
#define CLEAN 0

typedef struct stack {
    size_t size, used;
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

    new->data = data;
    new->size = 1;
    new->used = 0;

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

bool stack_is_empty(const Stack *stack) {
    return stack == NULL || stack->used == 0 || stack->size == 0;
}

/**
 * @brief Determine load factor of a Stack
 * 
 * @param stack Pointer to a Stack
 * @return float load factor
 */
static float stack_load_factor(const Stack *stack) {
    return (float)stack->used / (float)stack->size;
}

/**
 * @brief Resizes the Stack
 * 
 * @param stack Pointer to stack
 * @param growth Flag to grow/shrink/clean the stack
 * @return 0 on sucess, 1 allocation problems
 */
static int stack_resize(Stack *stack, int growth) {
    // double the size
    if (growth > 0) {
        stack->size *= 2;
    } else if (growth < 0) {
        // resize to 2/3
        stack->size *= 2;
        stack->size /= 3;
    }
    
    stack->data = realloc(stack->data, stack->size * sizeof(void *));
    if (stack->data == NULL)
        return 1;

    return 0;
}

int stack_push(Stack *stack, void *data) {
    if (stack == NULL || data == NULL)
        return 1;

    // double the size
    if (stack->used == stack->size) {
        if (stack_resize(stack, GROW) != 0)
            // allocation problems
            return 2;
    }

    stack->data[stack->used++] = data;
    return 0;
}

void *stack_pop(Stack *stack) {
    if (stack == NULL || stack->used == 0 || stack->size == 0)
        return NULL;

    if (stack_load_factor(stack) < 0.3) {
        if (stack_resize(stack, SHRINK) != 0)
            // allocation problems
            return NULL;
    }

    return stack->data[--stack->used];
}

void *stack_top(const Stack *stack) {
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

size_t stack_elements(const Stack *stack) {
    if (stack == NULL)
        return 0;
    return stack->used;
}

void show_stack(const Stack *stack, void (*show)(const void *, FILE *), FILE *fp) {
    if (stack != NULL && show != NULL && fp != NULL) {
        for (size_t i = 0; i < stack->used; i++)
            show(stack->data[stack->used - 1 - i], fp);
    }
}