#include "deque.h"
#include <stdio.h>
#include <utils.h>
#include <stdlib.h>

#define MAX 100

int main(void) {

    Deque *dq = create_deque();
    char *temp = NULL;
    FILE *fp = stdout;

    fprintf(fp, "--- PUSH FRONT ---\n");
    temp = random_string(7);
    deque_push_front(dq, create_person(temp, rand() % MAX));
    free(temp);

    temp = random_string(7);
    deque_push_front(dq, create_person(temp, rand() % MAX));
    free(temp);

    temp = random_string(7);
    deque_push_front(dq, create_person(temp, rand() % MAX));
    free(temp);
    
    show_deque(dq, &show_person, stdout);

    fprintf(fp, "--- PUSH BACK ---\n");
    temp = random_string(7);
    deque_push_back(dq, create_person(temp, rand() % MAX));
    free(temp);

    temp = random_string(7);
    deque_push_back(dq, create_person(temp, rand() % MAX));
    free(temp);

    temp = random_string(7);
    deque_push_back(dq, create_person(temp, rand() % MAX));
    free(temp);
    
    show_deque(dq, &show_person, stdout);

    fprintf(stdout, "\nQueue size: %ld\n", deque_size(dq));

    fprintf(stdout, "--- REVERSE ---\n");
    deque_reverse(dq);
    show_deque(dq, &show_person, stdout);

    fprintf(fp, "--- POP FRONT ---\n");
    deque_pop_front(dq);
    deque_pop_front(dq);
    show_deque(dq, &show_person, stdout);

    fprintf(fp, "--- POP BACK ---\n");
    deque_pop_back(dq);
    deque_pop_back(dq);
    show_deque(dq, &show_person, stdout);

    fprintf(stdout, "--- REVERSE ---\n");
    deque_reverse(dq);
    show_deque(dq, &show_person, stdout);

    deque_pop_front(dq);
    deque_pop_back(dq);
    show_deque(dq, &show_person, stdout);

    fprintf(fp, "Queue is empty: '%s'\n", deque_is_empty(dq) ? "true" : "false");

    destroy_deque(dq, &destroy_person);

    return 0;
}
