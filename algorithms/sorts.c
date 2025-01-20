#include "sorts.h"
#include <string.h>

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2


bool is_ordered(const void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    bool result = true;
    for (size_t i = 1; i < n_memb && result == true; i++) {
        if (compare(base + (i - 1) * size, base + i * size) > 0)
            result = false;
    }

    return result;
}

/**
 * @brief Swaps the values that are in index1 and index2 of the array
 * pre: index1 and index2 are valid indexes
 * 
 * @param base Array to make the change
 * @param index1 Position 1
 * @param index2 Position 2
 * @param size Size of each element of the array
 */
static void swap(void *base, size_t index1, size_t index2, size_t size) {
    unsigned char temp[size];
    memcpy(temp, base + (index1 * size), size);
    memcpy(base + (index1 * size), base + (index2 * size), size);
    memcpy(base + (index2 * size), temp, size);
}

void bubble_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    if (n_memb < 2)
        return;

    for (size_t i = n_memb - 1; i > 0; i--) {
        for (size_t j = 1; j <= i; j++) {
            if (compare(base + (j - 1) * size, base + j * size) > 0)
                swap(base, j - 1, j, size);
        }
    }
}

void selection_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    for (size_t i = 0, min; i < n_memb; i++) {
        min = i;
        for (size_t j = i + 1; j < n_memb; j++) {
            if (compare(base + j * size, base + min * size) < 0)
                min = j;
        }

        if (i != min)
            swap(base, min, i, size);
    }
}

void insertion_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    for (size_t i = 1; i < n_memb; i++) {
        for (size_t j = i; j > 0 && compare(base + j * size, base + (j - 1) * size) < 0; j--)
            swap(base, j, j - 1, size);
    }
}

/**
 * @brief Breaks the array in two, first come the elements smaller than pivot, and then come the rest of the elements
 * pre: base and compare are not NULL, and n_memb > 0
 * 
 * @param base Array
 * @param size Size of each element on the array
 * @param n_memb Number of elements in the array
 * @param compare Function to compare the elements of the array
 * @return size_t Position in each the pivot point is
 */
static size_t partition(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    // pivot point is the last position
    size_t pivot = n_memb - 1, next = 0, i;
    for (i = 0; i < n_memb; i++) {
        // if pivot is bigger
        if (compare(base + i * size, base + pivot * size) < 0) {
            swap(base, next, i, size);
            next++;
        }
    }

    swap(base, pivot, next, size);

    return next;
}

void quick_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    if (n_memb < 2)
        return;

    size_t pivot = partition(base, size, n_memb, compare);
    quick_sort(base, size, pivot, compare);
    quick_sort(base + (pivot + 1) * size, size, n_memb - pivot - 1, compare);
}

/**
 * @brief Merge the content of two ordered arrays
 * 
 * This function assumes result has enough space for n_memb1 + n_memb2 elements
 * 
 * @param base1 First array
 * @param n_memb1 Number of elements of base1
 * @param base2 Second array
 * @param n_memb2 Number of elements of base2
 * @param result Array to store the result
 * @param size Size of each element on the array
 * @param compare Compare function
 */
static void merge(const void *base1, size_t n_memb1, const void *base2, size_t n_memb2, void *result, size_t size, int (*compare)(const void *, const void *)) {
    size_t j = 0, i = 0, t = 0;
    while (i < n_memb1 && j < n_memb2) {
        if (compare(base1 + i * size, base2 + j * size) < 0){
            memcpy(result + t * size, base1 + i * size, size);
            i++;
        }
        else {
            memcpy(result + t * size, base2 + j * size, size);
            j++;
        }
        t++;
    }

    while (i < n_memb1) {
        memcpy(result + t * size, base1 + i * size, size);
        t++;
        i++;
    }

    while (j < n_memb2) {
        memcpy(result + t * size, base2 + j * size, size);
        t++;
        j++;
    }
}

/**
 * @brief Copies the content of an array to another
 * pre: dest and src != NULL
 * 
 * @param dest Destiny array
 * @param src Source array
 * @param size Size of each element
 * @param n_memb Number of elements on the src array
 */
static void copy(void *dest, const void *src, size_t size, size_t n_memb) {
    for (size_t i = 0; i < n_memb; i++)
        memcpy(dest + i * size, src + i * size, size);
}

void merge_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    if (n_memb < 2)
        return;

    size_t half = n_memb / 2;
    unsigned char temp[size * n_memb];
    merge_sort(base, size, half, compare);
    merge_sort(base + half * size, size, n_memb - half, compare);
    merge(base, half, base + half * size, n_memb - half, temp, size, compare);
    copy(base, temp, size, n_memb);
}

/**
 * @brief Repeatedly swaps a node with its parent until the property is satisfied or the root is reached
 * 
 * @param base Array
 * @param size Size of each element on the array
 * @param index Number of elements on the array
 * @param compare Function to compare elements
 */
static void bubble_up(void *base, size_t size, size_t index, int (*compare)(const void *, const void *)) {
    size_t up = PARENT(index);

    while (index > 0 && compare(base + index * size, base + up * size) > 0) {
        swap(base, index, up, size);
        index = up;
        up = PARENT(index);
    }
}

/**
 * @brief Repeatedly swaps a node with its largest child until the property is satisfied or a leaf is reached
 * 
 * @param base Array
 * @param size Size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
static void bubble_down(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    size_t index = 0;
    size_t pivot = LEFT(index);

    while (pivot < n_memb) {
        if (pivot + 1 < n_memb && compare(base + pivot * size, base + (pivot + 1)  * size) < 0)
            pivot = pivot + 1;

        if (compare(base + pivot * size, base + index * size) < 0)
            break;
        swap(base, pivot, index, size);
        index = pivot;
        pivot = LEFT(index);
    }
}

/**
 * @brief Builds a MAX heap
 * 
 * @param base Array
 * @param size Size of each element on the array
 * @param n_memb Number of elements on the array
 * @param compare Function to compare elements
 */
static void heapify(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    for (size_t i = 1; i < n_memb; i++)
        bubble_up(base, size, i, compare);
}

void heap_sort(void *base, size_t size, size_t n_memb, int (*compare)(const void *, const void *)) {
    if (n_memb < 2)
        return;

    // turn the array in a max heap
    heapify(base, size, n_memb, compare);

    for (size_t i = n_memb - 1; i > 0; i--) {
        swap(base, 0, i, size);
        bubble_down(base, size, i, compare);
    }
}