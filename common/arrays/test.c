#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void show_int(void *data, FILE *fp) {
    if (data != NULL)
        fprintf(fp, "%d ", *(int *)data);
}

int compare_int(const void *integer1, const void *integer2) {
    return *(size_t *)integer1 - *(size_t *)integer2;
}

int main(void) {
    srand(time(0));

    Array *arr = create_array(sizeof(int), 0);

    int temp = 0;
    for (int i = 0; i < MAX / 2; i++) {
        temp = rand() % MAX;
        array_append(arr, temp);
    }

    temp = 500;
    array_preppend(arr, temp);
    array_preppend(arr, temp);

    show_array(arr, &show_int, stdout);
    printf("\n");
    array_sort(arr, &compare_int);
    show_array(arr, &show_int, stdout);
    printf("\n");

    array_pop(arr, &temp);
    printf("temp: %d\n", temp);
    array_pop(arr, &temp);
    array_pop(arr, &temp);
    printf("temp: %d\n", temp);
    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("size: %ld\n", array_size(arr));

    int index = rand() % (MAX / 2);
    array_index(arr, index, &temp);
    printf("value at index %d: %d\n", index, temp);

    index = rand() % (MAX / 2);
    array_index(arr, index, &temp);
    printf("value at index %d: %d\n", index, temp);

    temp = rand() % MAX;
    printf("temp: %d\n", temp);
    array_insert(arr, temp, 3);
    temp = rand() % MAX;
    printf("temp: %d\n", temp);
    array_insert(arr, temp, 100);
    temp = rand() % MAX;
    printf("temp: %d\n", temp);
    array_insert(arr, temp, 300);
    
    show_array(arr, &show_int, stdout);
    printf("\n");

    array_remove(arr, &temp, 0);
    array_remove(arr, &temp, 1);
    array_remove(arr, &temp, 2);
    array_remove(arr, &temp, 0);
    array_remove(arr, &temp, 300);

    show_array(arr, &show_int, stdout);
    printf("\n");

    return 0;
}