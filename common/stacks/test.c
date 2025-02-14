#include "stack.h"
#include <utils.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 7
#define MAX_AGE 100

int main(void) {

    FILE *output = stdout;
    // FILE *output = fopen("out.txt", "w");
    char *temp = NULL;

    fprintf(output, "--- STACKS ---\n");

    Stack *st = stack_create();

    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    fprintf(output, "--- PUSH ---\n");
    for (int i = 0; i < 10; i++) {
        temp = random_string(STR_SIZE);
        stack_push(st, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }

    show_stack(st, &show_person, output);
    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    Person *trash = NULL;
    trash = stack_top(st);
    if (trash != NULL) {
        fprintf(output, "top: ");
        show_person(trash, output);
    } else
        fprintf(output, "stack is empty\n");


    fprintf(output, "--- POP ---\n");
    for (int i = 0; i < 3; i++) {
        trash = stack_pop(st);
        if (trash != NULL) {
            fprintf(output, "removed: ");
            show_person(trash, output);
            destroy_person(trash);
        } else
            fprintf(output, "stack is empty\n");
    }

    show_stack(st, &show_person, output);
    fprintf(output, "stack is empty: '%s'\n", stack_is_empty(st) ? "true" : "false");
    fprintf(output, "stack size: %lu\n", stack_elements(st));

    trash = stack_top(st);
    if (trash != NULL) {
        fprintf(output, "top: ");
        show_person(trash, output);
    } else
        fprintf(output, "stack is empty\n");

    stack_destroy(st, &destroy_person);

    return 0;
}