#include "sorts.h"
#include "search.h"
#include <utils.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(sorts, has_order) {
    cr_expect(true, "This test will fail.");
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");
    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Inverted array.");
} 

Test(sorts, bubblesort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    bubble_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    bubble_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    bubble_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    bubble_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(sorts, selectionsort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    selection_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    selection_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    selection_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    selection_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(sorts, insertionsort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    insertion_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    insertion_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    insertion_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    insertion_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(sorts, quicksort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    quick_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    quick_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    quick_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    quick_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(sorts, mergesort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    merge_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    merge_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    merge_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    merge_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(sorts, heapsort) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    heap_sort(arr, sizeof(int), 0, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 0, &compare_int), "Empty array must be ordered.");

    heap_sort(arr, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(arr, sizeof(int), 10, &compare_int), "Ordered array.");

    int no_order[10] = {4,1,5,3,1,0,5,9,-3,10};
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    heap_sort(no_order, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(no_order, sizeof(int), 10, &compare_int), "Array with no order.");

    int reverse_array[10] = {10,9,8,7,6,5,4,3,2,1};
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int) == false, "Array with no order.");
    heap_sort(reverse_array, sizeof(int), 10, &compare_int);
    cr_expect(is_ordered(reverse_array, sizeof(int), 10, &compare_int), "Array with no order.");
}

Test(search, linear) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int temp = 8;
    cr_expect(linear_search(arr, sizeof(int), 10, &compare_int, &temp) == 7, "Finding 8");
    temp = 20;
    cr_expect(linear_search(arr, sizeof(int), 10, &compare_int, &temp) == -1, "Value not on the array.");
    cr_expect(linear_search(arr, sizeof(int), 0, &compare_int, &temp) == -1, "Empty array.");
}

Test(search, binary) {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int temp = 8;
    cr_expect(linear_search(arr, sizeof(int), 10, &compare_int, &temp) == 7, "Finding 8");
    temp = 20;
    cr_expect(linear_search(arr, sizeof(int), 10, &compare_int, &temp) == -1, "Value not on the array.");
    cr_expect(linear_search(arr, sizeof(int), 0, &compare_int, &temp) == -1, "Empty array.");
}