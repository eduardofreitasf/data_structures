#include "queue.h"
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
    Queue *queue = queue_create();
    int i = 0, temp = 0;
    void *trash = NULL;

    show_queue(queue, &show_int, output);
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- ENQUEUE ---\n");
    for (i = 0; i < 20; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "enqueue %d\n", temp);
        enqueue(queue, create_int(temp));
    }
    show_queue(queue, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- FRONT ---\n");
    trash = queue_front(queue);
    if (trash != NULL)
        fprintf(output, "front: %d\n", *(int *)trash);

    fprintf(output, "--- BACK ---\n");
    trash = queue_back(queue);
    if (trash != NULL)
        fprintf(output, "back: %d\n", *(int *)trash);

    fprintf(output, "--- ENQUEUE ---\n");
    for (i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "enqueue %d\n", temp);
        enqueue(queue, create_int(temp));
    }
    show_queue(queue, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- DEQUEUE ---\n");
    for (i = 0; i < 15; i++) {
        trash = dequeue(queue);
        if (trash != NULL) {
            fprintf(output, "dequeue %d\n", *(int *)trash);
            free(trash);
        } else
            fprintf(output, "queue is empty or error\n");
    }
    show_queue(queue, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- FRONT ---\n");
    trash = queue_front(queue);
    if (trash != NULL)
        fprintf(output, "front: %d\n", *(int *)trash);

    fprintf(output, "--- BACK ---\n");
    trash = queue_back(queue);
    if (trash != NULL)
        fprintf(output, "back: %d\n", *(int *)trash);

    fprintf(output, "--- DEQUEUE ---\n");
    for (i = 0; i < 10; i++) {
        trash = dequeue(queue);
        if (trash != NULL) {
            fprintf(output, "dequeue %d\n", *(int *)trash);
            free(trash);
        } else
            fprintf(output, "queue is empty or error\n");
    }
    show_queue(queue, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- ENQUEUE ---\n");
    for (i = 0; i < 13; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "enqueue %d\n", temp);
        enqueue(queue, create_int(temp));
    }
    show_queue(queue, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    fprintf(output, "--- CLEAR ---\n");
    queue_clear(queue, &free);
    show_queue(queue, &show_int, output);
    fprintf(output, "queue size: %lu\n", queue_size(queue));
    fprintf(output, "queue is empty: '%s'\n", queue_is_empty(queue) ? "true" : "false");

    queue_destroy(queue, &free);

    return 0;
}