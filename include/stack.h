#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

/**
 * @brief Creates a Stack
 *
 * @param duplicate Duplicates data
 * @param free_data Frees data
 * @param show_data Shows data
 * @return Stack* Stack
 */
Stack *stack_create(void *(*duplicate)(void *), void (*free_data)(void *),
                    void (*show_data)(void *));

/**
 * @brief Adds an element to the top of a Stack
 *
 * @param stack Stack
 * @param data Data to be stored
 */
void push(Stack *stack, void *data);

/**
 * @brief Removes an element from the top of the stack
 *
 * @param stack Stack
 * @return void* Data stored at the top
 */
void *pop(Stack *stack);

/**
 * @brief Duplicates the top element
 *
 * @param stack Stack
 * @return void* Data stored at the top
 */
void *top(Stack *stack);

/**
 * @brief Shows every element of the stack
 *
 * @param stack Stack
 */
void show_stack(Stack *stack);

/**
 * @brief Frees a stack
 *
 * @param stack Stack
 */
void free_stack(Stack *stack);

#endif