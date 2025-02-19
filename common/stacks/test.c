#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 100

void show_int(const void *data, FILE *fp) {
    if (data != NULL && fp != NULL)
        fprintf(fp, "%d ", *(int *)data);
}

void *create_int(int value) {
    int *new = malloc(sizeof(int));
    *new = value;

    return new;
}

int main(void) {
    srand(time(0));

    FILE *output = stdout;
    void *trash = NULL;
    int temp = 0;
    Stack *st = stack_create();

    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    fprintf(output, "--- PUSH ---\n");
    for (int i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push %d\n", temp);
        stack_push(st, create_int(temp));
    }

    show_stack(st, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    trash = stack_top(st);
    if (trash != NULL)
        fprintf(output, "top of stack: %d\n", *(int *)trash);

    fprintf(output, "--- CLEAR ---\n");
    stack_clear(st, &free);

    fprintf(output, "--- PUSH ---\n");
    for (int i = 0; i < 15; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push %d\n", temp);
        stack_push(st, create_int(temp));
    }
    show_stack(st, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    fprintf(output, "--- POP ---\n");
    for (int i = 0; i < 4; i++) {
        trash = stack_pop(st);
        if (trash != NULL) {
            fprintf(output, "pop %d\n", *(int *)trash);
            free(trash);
        }
    }
    show_stack(st, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    stack_destroy(st, &free);

    return 0;
}