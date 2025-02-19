#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>

typedef struct stack Stack;

/**
 * @brief Allocates space for a Stack
 * 
 * @return Stack pointer
 */
Stack *stack_create(void);

/**
 * @brief Frees the space occupied by a Stack and it's elements
 * 
 * @param stack Stack
 * @param destroy Function to free the data stored
 */
void stack_destroy(Stack *stack, void (*destroy)(void *));

/**
 * @brief Checks if a Stack is empty
 * 
 * @param stack Stack
 * @return true Stack is empty
 * @return false Stack is not empty
 */
bool stack_is_empty(const Stack *stack);

/**
 * @brief Adds data to the top of the stack
 * 
 * @param stack Stack
 * @param data Data to store
 */
int stack_push(Stack *stack, void *data);

/**
 * @brief Removes the element on top of the Stack
 * 
 * @param stack Stack
 * @return Element on the top of the Stack (NULL if stack is empty)
 */
void *stack_pop(Stack *stack);

/**
 * @brief Peeks the element on the top of the Stack
 * 
 * @param stack Stack
 * @return Element on the top of the Stack (NULL if stack is empty)
 */
void *stack_top(const Stack *stack);

/**
 * @brief Emptys the Stack
 * 
 * @param stack Stack
 * @param destroy Function to free the elements on the Stack
 */
void stack_clear(Stack *stack, void (*destroy)(void *));

/**
 * @brief Calculates the size of the Stack
 * 
 * @param stack Stack
 * @return Number of elements on the Stack
 */
size_t stack_elements(const Stack *stack);

/**
 * @brief Shows the content of a Stack
 * 
 * @param stack Stack
 * @param show Function to show the content stored
 * @param fp File pointer
 */
void show_stack(const Stack *stack, void (*show)(const void *, FILE *), FILE *fp);

#endif
