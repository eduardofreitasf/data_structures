#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>

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
    FILE *output = stdout;
    int temp = 0, i = 0;
    void *trash = NULL;
    CQueue *cq = create_cqueue();
    
    fprintf(output, "queue size: %lu\n", cqueue_size(cq));
    fprintf(output, "queue is empty: '%s'\n", cqueue_is_empty(cq)? "true" : "false");

    fprintf(output, "--- ENQUEUE ---\n");
    for (i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "enqueue %d\n", temp);
        cqueue_enqueue(cq, create_int(temp));
    }
    show_cqueue(cq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", cqueue_size(cq));
    fprintf(output, "queue is empty: '%s'\n", cqueue_is_empty(cq)? "true" : "false");

    fprintf(output, "--- FRONT ---\n");
    trash = cqueue_front(cq);
    if (trash != NULL)
        fprintf(output, "front: %d\n", *(int *)trash);

    fprintf(output, "--- BACK ---\n");
    trash = cqueue_back(cq);
    if (trash != NULL)
        fprintf(output, "back: %d\n", *(int *)trash);

    fprintf(output, "--- CLEAR ---\n");
    cqueue_clear(cq, &free);
    fprintf(output, "queue size: %lu\n", cqueue_size(cq));
    fprintf(output, "queue is empty: '%s'\n", cqueue_is_empty(cq)? "true" : "false");

    fprintf(output, "--- ENQUEUE ---\n");
    for (i = 0; i < 15; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "enqueue %d\n", temp);
        cqueue_enqueue(cq, create_int(temp));
    }
    show_cqueue(cq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", cqueue_size(cq));
    fprintf(output, "queue is empty: '%s'\n", cqueue_is_empty(cq)? "true" : "false");

    fprintf(output, "--- DEQUEUE ---\n");
    for (i = 0; i < 7; i++) {
        trash = cqueue_dequeue(cq);
        if (trash != NULL) {
            fprintf(output, "dequeue %d\n", *(int *)trash);
            free(trash);
        } else
            fprintf(output, "circular queue is empty or error\n");
    }
    show_cqueue(cq, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", cqueue_size(cq));
    fprintf(output, "queue is empty: '%s'\n", cqueue_is_empty(cq)? "true" : "false");

    destroy_cqueue(cq, &free);

    return 0;
}