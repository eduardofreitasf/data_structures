#include "queue.h"
#include <utils.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 7
#define MAX_AGE 100

int main(void) {
    FILE *fp = stdout;
    Queue *q = queue_create();
    show_person(queue_back(q), fp);
    show_person(queue_front(q), fp);

    dequeue(q);
    dequeue(q);

    char *temp = NULL;

    fprintf(fp, "--- ENQUEUE ---\n");
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);

    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);

    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);

    show_queue(q, &show_person, fp);

    fprintf(fp, "--- FRONT ---\n");
    show_person(queue_front(q), fp);

    fprintf(fp, "--- BACK ---\n");
    show_person(queue_back(q), fp);

    fprintf(fp, "--- ENQUEUE ---\n");
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);
    temp = random_string(STR_SIZE);
    enqueue(q, create_person(temp, rand() % MAX_AGE));
    free(temp);

    show_queue(q, &show_person, fp);

    fprintf(fp, "Queue Size: %ld\n", queue_size(q));

    fprintf(fp, "--- DEQUEUE ---\n");
    show_person(dequeue(q), fp);
    show_person(dequeue(q), fp);
    show_person(dequeue(q), fp);

    fprintf(fp, "--- RESULT ---\n");
    show_queue(q, &show_person, fp);
    fprintf(fp, "Queue Size: %ld\n", queue_size(q));

    fprintf(fp, "--- CLEANNING ---\n");
    queue_clear(q, &destroy_person);
    show_queue(q, &show_person, fp);
    fprintf(fp, "Queue Size: %ld\n", queue_size(q));

    fprintf(fp, "--- ENQUEUE ---\n");
    for (int i = 0; i < 5; i++) {
        temp = random_string(STR_SIZE);
        enqueue(q, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }

    show_queue(q, &show_person, fp);
    fprintf(fp, "Queue Size: %ld\n", queue_size(q));

    queue_destroy(q, &destroy_person);

    return 0;
}