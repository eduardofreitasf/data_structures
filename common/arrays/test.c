#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utils.h>

#define MAX 100

int main(void) {
    srand(time(0));

    Array *arr = create_array(sizeof(int), 0);

    printf("APPEND\n");
    int temp = 0;
    for (int i = 0; i < MAX / 2; i++) {
        temp = rand() % MAX;
        array_append(arr, temp);
    }
    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("size: %ld\n", array_size(arr));

    printf("PREPPEND\n");
    temp = 500;
    array_preppend(arr, temp);
    array_preppend(arr, temp);

    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("SORTING\n");
    array_sort(arr, &compare_int);
    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("size: %ld\n", array_size(arr));

    printf("POP\n");
    array_pop(arr, &temp);
    printf("temp: %d\n", temp);
    array_pop(arr, &temp);
    printf("temp: %d\n", temp);
    array_pop(arr, &temp);
    printf("temp: %d\n", temp);
    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("size: %ld\n", array_size(arr));

    printf("INDEX\n");
    int index = rand() % (MAX / 2);
    array_index(arr, index, &temp);
    printf("value at index %d: %d\n", index, temp);

    index = rand() % (MAX / 2);
    array_index(arr, index, &temp);
    printf("value at index %d: %d\n", index, temp);

    printf("INSERT\n");
    temp = rand() % MAX;
    printf("insert %d at %d\n", temp, 3);
    array_insert(arr, temp, 3);
    temp = rand() % MAX;
    printf("insert %d at %d\n", temp, 100);
    array_insert(arr, temp, 100);
    temp = rand() % MAX;
    printf("insert %d at %d\n", temp, 30);
    array_insert(arr, temp, 300);
    
    show_array(arr, &show_int, stdout);
    printf("\n");

    printf("REMOVE\n");
    array_remove(arr, &temp, 0);
    printf("removed from %d: %d\n", 0, temp);

    array_remove(arr, &temp, 4);
    printf("removed from %d: %d\n", 4, temp);

    array_remove(arr, &temp, 30);
    printf("removed from %d: %d\n", 30, temp);

    array_remove(arr, &temp, 40);
    printf("removed from %d: %d\n", 40, temp);

    array_remove(arr, &temp, 300);
    printf("removed from %d: %d\n", 300, temp);

    show_array(arr, &show_int, stdout);
    printf("\n");

    destroy_array(arr, true);

    return 0;
}