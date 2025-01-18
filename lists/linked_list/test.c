#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <time.h>
#include "list.h"

#define MAX_AGE 100
#define STR_SIZE 7

int main(void) {
    srand(time(0));
    // FILE *fp = fopen("result.log", "w");
    FILE *fp = stdout;
    char *temp = NULL;

    List *l = list_create();
    fprintf(fp, "Is EMPTY: '%s'\n", list_is_empty(l) ? "true" : "false");
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");

    fprintf(fp, "--- PREPPENDING ---\n");
    for (int i = 0; i < 4; i++) {
        temp = random_string(STR_SIZE);
        list_preppend(l, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }
    show_list(l, &show_person, fp);

    fprintf(fp, "SIZE: %ld\n", list_size(l));
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");

    fprintf(fp, "--- APPENDING ---\n");
    for (int i = 0; i < 4; i++) {
        temp = random_string(STR_SIZE);
        list_append(l, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }
    show_list(l, &show_person, fp);

    fprintf(fp, "SIZE: %ld\n", list_size(l));
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");
    fprintf(fp, "Is EMPTY: '%s'\n", list_is_empty(l) ? "true" : "false");

    fprintf(fp, "--- CLONE ---\n");
    List * clone = list_clone(l, &duplicate_person);
    show_list(clone, &show_person, fp);

    fprintf(fp, "--- MIN ---\n");
    Person * p1 = list_min(l, &compare_person);
    show_person(p1, fp);
    p1 = list_remove(l, p1, &compare_person);
    destroy_person(p1);
    fprintf(fp, "--- MAX ---\n");
    p1 = list_max(l, &compare_person);
    show_person(p1, fp);

    fprintf(fp, "--- REMOVE (min and max) ---\n");
    p1 = list_remove(l, p1, &compare_person);
    destroy_person(p1);
    show_list(l, &show_person, fp);

    fprintf(fp, "--- REVERSE ---\n");
    list_reverse(l);
    show_list(l, &show_person, fp);

    fprintf(fp, "--- INSERT WITH ORDER ---\n");
    List *with_order = list_create();
    for (int i = 0; i < 15; i++) {
        temp = random_string(STR_SIZE);
        list_insert(with_order, create_person(temp, rand() % MAX_AGE), &compare_person);
        free(temp);
    }
    show_list(with_order, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(with_order, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(with_order));

    fprintf(fp, "--- MIN ---\n");
    p1 = list_min(with_order, &compare_person);
    show_person(p1, fp);
    fprintf(fp, "--- MAX ---\n");
    p1 = list_max(with_order, &compare_person);
    show_person(p1, fp);

    fprintf(fp, "--- CONCAT ---\n");
    l = list_concat(l, clone);
    show_list(l, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", list_size(l));
    list_destroy(clone, &destroy_person);

    fprintf(fp, "--- TAKE ---\n");
    clone = list_take(l, 4);
    show_list(l, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", list_size(l));

    fprintf(fp, "--- REMAINDER ---\n");
    show_list(clone, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", list_size(clone));

    fprintf(fp, "--- DROP ---\n");
    List *remainder = list_drop(clone, 5);
    show_list(clone, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", list_size(clone));

    fprintf(fp, "--- REMAINDER ---\n");
    show_list(remainder, &show_person, fp);
    fprintf(fp, "SIZE: %ld\n", list_size(remainder));

    list_destroy(l, &destroy_person);
    list_destroy(with_order, &destroy_person);
    list_destroy(remainder, &destroy_person);
    list_destroy(clone, &destroy_person);

    fprintf(fp, "--- INSERT WITH ORDER ---\n");
    with_order = list_create();
    for (int i = 0; i < 5; i++) {
        temp = random_string(STR_SIZE);
        list_insert(with_order, create_person(temp, rand() % MAX_AGE), &compare_person);
        free(temp);
    }
    show_list(with_order, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(with_order, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(with_order));

    fprintf(fp, "--- INSERT WITH ORDER ---\n");
    l = list_create();
    for (int i = 0; i < 4; i++) {
        temp = random_string(STR_SIZE);
        list_insert(l, create_person(temp, rand() % MAX_AGE), &compare_person);
        free(temp);
    }
    show_list(l, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(l));

    fprintf(fp, "--- MERGE ---\n");
    l = list_merge(l, with_order, &compare_person);
    show_list(l, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(l));

    list_destroy(with_order, &destroy_person);
    list_destroy(l, &destroy_person);

    fprintf(fp, "--- NEW LIST ---\n");
    l = list_create();
    for (int i = 0; i < 10; i++) {
        temp = random_string(STR_SIZE);
        list_preppend(l, create_person(temp, rand() % MAX_AGE));
        free(temp);
    }
    show_list(l, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(l));

    fprintf(fp, "--- SORTING ---\n");
    list_sort(l, &compare_person);
    show_list(l, &show_person, fp);
    fprintf(fp, "ORDER '%s'\n", list_order(l, &compare_person) ? "true" : "false");
    fprintf(fp, "SIZE: %ld\n", list_size(l));

    list_destroy(l, &destroy_person);

    return 0;
}