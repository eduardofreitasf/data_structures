#include "deque.h"
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
    int temp = 0, i = 0;
    void *trash = NULL;

    Deque *dq = create_deque();
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- PUSH FRONT ---\n");
    for (i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push front %d\n", temp);
        deque_push_front(dq, create_int(temp));
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- PUSH BACK ---\n");
    for (i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push front %d\n", temp);
        deque_push_back(dq, create_int(temp));
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- FRONT ---\n");
    trash = deque_front(dq);
    if (trash != NULL)
        fprintf(output, "front: %d\n", *(int *)trash);

    fprintf(output, "--- BACK ---\n");
    trash = deque_back(dq);
    if (trash != NULL)
        fprintf(output, "back: %d\n", *(int *)trash);

    fprintf(output, "--- POP FRONT ---\n");
    for (i = 0; i < 5; i++) {
        trash = deque_pop_front(dq);
        if (trash != NULL) {
            fprintf(output, "pop front %d\n", *(int *)trash);
            free(trash);
        } else
            fprintf(output, "deque is empty or error\n");
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- FRONT ---\n");
    trash = deque_front(dq);
    if (trash != NULL)
        fprintf(output, "front: %d\n", *(int *)trash);

    fprintf(output, "--- BACK ---\n");
    trash = deque_back(dq);
    if (trash != NULL)
        fprintf(output, "back: %d\n", *(int *)trash);

    fprintf(output, "--- POP BACK ---\n");
    for (i = 0; i < 5; i++) {
        trash = deque_pop_back(dq);
        if (trash != NULL) {
            fprintf(output, "pop back %d\n", *(int *)trash);
            free(trash);
        } else
            fprintf(output, "deque is empty or error\n");
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- REVERSE ---\n");
    deque_reverse(dq);
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- PUSH FRONT ---\n");
    for (i = 0; i < 5; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push front %d\n", temp);
        deque_push_front(dq, create_int(temp));
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    fprintf(output, "--- PUSH BACK ---\n");
    for (i = 0; i < 5; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "push front %d\n", temp);
        deque_push_back(dq, create_int(temp));
    }
    show_deque(dq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "deque size: %lu\n", deque_size(dq));
    fprintf(output, "deque is empty: '%s'\n", deque_is_empty(dq)? "true" : "false");

    destroy_deque(dq, &free);

    return 0;
}