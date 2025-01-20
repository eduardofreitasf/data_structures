#include "sorts.h"
#include <time.h>
#include <stdio.h>
#include <utils.h>
#include <stdlib.h>

#define MAX_VALUE 100
#define STR_SIZE 9

int main(int argc, char **argv) {
    srand(time(0));

    if (argc < 2) {
        fprintf(stdout, "Usage: '%s' <array size>\n", argv[0]);
        return 1;
    }

    size_t array_size = atoi(argv[1]);
    if (array_size == 0) {
        fprintf(stdout, "Invalid array size\n");
        return 2;
    }
    char *original_file = "arrays.txt";
    char *sorted_file = "sorted.txt";
    FILE *output = fopen(original_file, "w");
    FILE *sorted = fopen(sorted_file, "w");

    char *temp = NULL;
    size_t sorted_array[array_size];
    size_t reverse_array[array_size];
    size_t random_array[array_size];
    struct timespec start, end;
    double elapsed_time = 0;

    int choice = 0;
    do {
        fprintf(stdout, "Select a Sorting Algorithm:\n");
        fprintf(stdout, "1 - Bubble Sort\n2 - Selection Sort\n");
        fprintf(stdout, "3 - Insertion Sort\n4 - Quick Sort\n");
        fprintf(stdout, "5 - Merge Sort\n6 - Heap Sort\n");
        fprintf(stdout, "choice: ");
        scanf("%d", &choice);
    } while (choice > 6 || choice < 1);

    void (*sort)(void *, size_t , size_t , int (*)(const void *, const void *));

    switch (choice) {
    case 1:
        sort = bubble_sort;
        fprintf(stdout, "--- BUBBLE SORT ---\n");
        break;
    case 2:
        sort = selection_sort;
        fprintf(stdout, "--- SELECTION SORT ---\n");
        break;
    case 3:
        sort = insertion_sort;
        fprintf(stdout, "--- INSERTION SORT ---\n");
        break;
    case 4:
        sort = quick_sort;
        fprintf(stdout, "--- QUICK SORT ---\n");
        break;
    case 5:
        sort = merge_sort;
        fprintf(stdout, "--- MERGE SORT ---\n");
        break;
    case 6:
        sort = heap_sort;
        fprintf(stdout, "--- HEAP SORT ---\n");
        break;
    default:
        break;
    }

    size_t iterate;
    for (iterate = 0; iterate < array_size; iterate++) {
        temp = random_string(STR_SIZE);
        sorted_array[iterate] = iterate;
        reverse_array[iterate] = array_size - 1 - iterate;
        random_array[iterate] = rand() % MAX_VALUE;
        free(temp);
    }

    fprintf(output, "--- SORTED ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(output, "%ld ", sorted_array[iterate]);

    fprintf(output, "\n--- INVERTED ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(output, "%ld ", reverse_array[iterate]);
    
    fprintf(output, "\n--- RANDOM ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(output, "%ld ", random_array[iterate]);

    fprintf(stdout, "[Sorted array]\n");
    clock_gettime(CLOCK_REALTIME, &start);
    sort(sorted_array, sizeof(size_t), array_size, &compare_int);
    clock_gettime(CLOCK_REALTIME, &end);
    fprintf(stdout, "order: '%s'\n", is_ordered(sorted_array, sizeof(size_t), array_size, &compare_int) ? "true" : "false");
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(stdout, "Time: %f seconds\n", elapsed_time);

    fprintf(stdout, "[Inverted array]\n");
    clock_gettime(CLOCK_REALTIME, &start);
    sort(reverse_array, sizeof(size_t), array_size, &compare_int);
    clock_gettime(CLOCK_REALTIME, &end);
    fprintf(stdout, "order: '%s'\n", is_ordered(reverse_array, sizeof(size_t), array_size, &compare_int) ? "true" : "false");
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(stdout, "Time: %f seconds\n", elapsed_time);

    fprintf(stdout, "[Random array]\n");
    clock_gettime(CLOCK_REALTIME, &start);
    sort(random_array, sizeof(size_t), array_size, &compare_int);
    clock_gettime(CLOCK_REALTIME, &end);
    fprintf(stdout, "order: '%s'\n", is_ordered(random_array, sizeof(size_t), array_size, &compare_int) ? "true" : "false");
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(stdout, "Time: %f seconds\n", elapsed_time);

    fprintf(sorted, "--- SORTED ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(sorted, "%ld ", sorted_array[iterate]);

    fprintf(sorted, "\n--- INVERTED ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(sorted, "%ld ", reverse_array[iterate]);
    
    fprintf(sorted, "\n--- RANDOM ARRAY ---\n");
    for (iterate = 0; iterate < array_size; iterate++)
        fprintf(sorted, "%ld ", random_array[iterate]);

    fprintf(stdout, "You can see the arrays in '%s' and '%s'.\n", original_file, sorted_file);

    return 0;
}
