#include "heap.h"
#include <utils.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 7
#define MAX_AGE 100

int main(void) {
    FILE *fp = stdout;
    char *temp = NULL;

    Heap *hp = create_heap(3);
    show_heap(hp, &show_person, fp);

    fprintf(fp, "--- INSERT ---\n");
    for (int i = 0; i < 15; i++) {
        temp = random_string(STR_SIZE);
        heap_insert(hp, create_person(temp, rand() % MAX_AGE), &compare_person);
        free(temp);
    }
    show_heap(hp, &show_person, fp);
    fprintf(fp, "SIZE %ld\n", heap_size(hp));

    fprintf(fp, "--- REMOVE ---\n");
    void *res = NULL;
    for (int i = 0; i < 5; i++) {
        res = heap_remove_root(hp, &compare_person);
        if (res != NULL)
            destroy_person(res);
    }
    show_heap(hp, &show_person, fp);
    fprintf(fp, "SIZE %ld\n", heap_size(hp));

    destroy_heap(hp, &destroy_person);

    return 0;
}