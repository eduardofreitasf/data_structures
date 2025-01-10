#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack Stack;

/*
 * Allocates space for a Stack
 */
Stack *stack_create(void);

/*
 * Liberates the space occupied by a Stack and it's elements
 */
void stack_destroy(Stack *stack, void (*destroy)(void *));

/*
 * Checks if a Stack is empty
 */
bool stack_is_empty(Stack *stack);

/*
 * Adds data to the top of the Stack
 */
void stack_push(Stack *stack, void *data);

/*
 * Removes the element on the top of the Stack
 * NULL if it is empty
 */
void *stack_pop(Stack *stack);

/*
 * Returns the top element of the Stack
 * NULL if it is empty
 */
void *stack_top(Stack *stack);

/*
 * Removes every element on the Stack
 */
void stack_clear(Stack *stack, void (*destroy)(void *));

/*
 * Returns the current size of the Stack
 */
unsigned stack_elements(Stack *stack);

#endif
