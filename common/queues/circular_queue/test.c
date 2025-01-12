#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

#define MAX_AGE 100
#define STR_SIZE 7

int main(void) {
    FILE *fp = stdout;
    char *temp = NULL;

    CQueue *cq = create_cqueue();
    show_cqueue(cq, &show_person, fp);
    fprintf(fp, "IS EMPTY: '%s'\n", cqueue_is_empty(cq) ? "true" : "false");

    fprintf(fp, "--- ENQUEUE ---\n");
    temp = random_string(STR_SIZE);
    cqueue_enqueue(cq, create_person(temp, rand() % MAX_AGE));
    free(temp);
    show_cqueue(cq, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", cqueue_size(cq));

    fprintf(fp, "--- DEQUEUE ---\n");
    show_person(cqueue_dequeue(cq), fp);
    show_person(cqueue_dequeue(cq), fp);
    fprintf(fp, "SIZE: %ld\n", cqueue_size(cq));

    fprintf(fp, "--- ENQUEUE ---\n");
    for (int i = 0; i < 10; i++) {
        temp = random_string(STR_SIZE);
        cqueue_enqueue(cq, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }
    show_cqueue(cq, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", cqueue_size(cq));
    fprintf(fp, "--- FRONT ---\n");
    show_person(cqueue_front(cq), fp);

    fprintf(fp, "--- BACK ---\n");
    show_person(cqueue_back(cq), fp);

    fprintf(fp, "--- DEQUEUE ---\n");
    show_person(cqueue_dequeue(cq), fp);
    show_person(cqueue_dequeue(cq), fp);
    show_person(cqueue_dequeue(cq), fp);
    
    fprintf(fp, "IS EMPTY: '%s'\n", cqueue_is_empty(cq) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", cqueue_size(cq));
    show_cqueue(cq, &show_person, fp);

    fprintf(fp, "--- CLEAR ---\n");
    cqueue_clear(cq, &destroy_person);
    show_cqueue(cq, &show_person, fp);
    fprintf(fp, "IS EMPTY: '%s'\n", cqueue_is_empty(cq) ? "true" : "false");

    destroy_cqueue(cq, &destroy_person);

    return 0;
}