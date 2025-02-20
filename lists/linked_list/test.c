#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VALUE 100

void *clone_int(const void *data) {
    int *new = (int *) malloc(sizeof(int));
    memcpy(new, data, sizeof(int));

    return new;
}

void show_int(const void *data, FILE *fp) {
    if (data != NULL && fp != NULL)
        fprintf(fp, "%d ", *(int *)data);
}

void *create_int(int value) {
    int *new = malloc(sizeof(int));
    *new = value;

    return new;
}

int compare_int(const void *value1, const void *value2) {
    return *(int *)value1 - *(int *)value2;
}

int main(void) {
    srand(time(0));

    FILE *output = stdout;
    int temp = 0;
    void *trash = NULL, *aux = NULL;

    List *ll = list_create();

    fprintf(output, "list is empty '%s'\n", list_is_empty(ll) ? "true" : "false");
    fprintf(output, "list size %lu\n", list_size(ll));

    fprintf(output, "--- APPEND ---\n");
    for (int i = 0; i < 15; i++) {
        temp = rand() % MAX_VALUE;
        if (list_append(ll, create_int(temp)) != 0)
            fprintf(output, "error ocurred in append\n");
        else
            fprintf(output, "append %d\n", temp);
    }
    show_list(ll, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "list is empty '%s'\n", list_is_empty(ll) ? "true" : "false");
    fprintf(output, "list size %lu\n", list_size(ll));

    fprintf(output, "--- PREPPEND ---\n");
    for (int i = 0; i < 15; i++) {
        temp = rand() % MAX_VALUE;
        if (list_preppend(ll, create_int(temp)) != 0)
            fprintf(output, "error ocurred in preppend\n");
        else
            fprintf(output, "preppend %d\n", temp);
    }
    show_list(ll, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "list is empty '%s'\n", list_is_empty(ll) ? "true" : "false");
    fprintf(output, "list size %lu\n", list_size(ll));
    fprintf(output, "list has order '%s'\n", list_order(ll, &compare_int) ? "true" : "false");

    fprintf(output, "--- CLONE ---\n");
    List *second = list_clone(ll, &clone_int);
    show_list(second, &show_int, output);
    fprintf(output, "\n");

    fprintf(output, "--- REVERSE ---\n");
    list_reverse(second);
    show_list(second, &show_int, output);
    fprintf(output, "\n");

    trash = list_min(second, &compare_int);
    if (trash != NULL)
        fprintf(output, "list min %d\n", *(int *)trash);

    trash = list_max(second, &compare_int);
    if (trash != NULL)
        fprintf(output, "list max %d\n", *(int *)trash);

    fprintf(output, "--- SORT ---\n");
    fprintf(output, "before:\n");
    show_list(ll, &show_int, output);
    fprintf(output, "\nafter:\n");
    list_sort(ll, &compare_int);
    show_list(ll, &show_int, output);

    fprintf(output, "\n--- CLEANUP ---\n");
    list_destroy(ll, &free);
    list_destroy(second, &free);

    ll = list_create();

    fprintf(output, "--- INSERT WITH ORDER ---\n");
    for (int i = 0; i < 10; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "insert %d\n", temp);
        list_insert(ll, create_int(temp), &compare_int);
    }

    show_list(ll, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "list size %lu\n", list_size(ll));
    fprintf(output, "list has order '%s'\n", list_order(ll, &compare_int) ? "true" : "false");

    fprintf(output, "insert 50\n");
    list_insert(ll, create_int(50), &compare_int);

    fprintf(output, "insert 30\n");
    list_insert(ll, create_int(30), &compare_int);

    fprintf(output, "insert 70\n");
    list_insert(ll, create_int(70), &compare_int);

    for (int i = 0; i < 3; i++) {
        temp = rand() % MAX_VALUE;
        fprintf(output, "insert %d\n", temp);
        list_insert(ll, create_int(temp), &compare_int);
    }

    show_list(ll, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "list size %lu\n", list_size(ll));    

    fprintf(output, "--- REMOVE ---\n");

    aux = create_int(50);
    trash = list_remove(ll, aux, &compare_int);
    if (trash != NULL) {
        fprintf(output, "removed %d\n", *(int *)trash);
        free(trash);
    }
    free(aux);

    aux = create_int(30);
    trash = list_remove(ll, aux, &compare_int);
    if (trash != NULL) {
        fprintf(output, "removed %d\n", *(int *)trash);
        free(trash);
    }
    free(aux);

    aux = create_int(70);
    trash = list_remove(ll, aux, &compare_int);
    if (trash != NULL) {
        fprintf(output, "removed %d\n", *(int *)trash);
        free(trash);
    }
    free(aux);

    aux = create_int(500);
    trash = list_remove(ll, aux, &compare_int);
    if (trash != NULL) {
        fprintf(output, "removed %d\n", *(int *)trash);
        free(trash);
    } else
        fprintf(output, "500 is not in the list\n");
    free(aux);

    show_list(ll, &show_int, output);
    fprintf(output, "\n");
    fprintf(output, "list size %lu\n", list_size(ll));



    list_destroy(ll, &free);

    return 0;
}