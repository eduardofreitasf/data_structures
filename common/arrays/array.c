#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

#define GROW 1
#define SHRINK (-1)
#define CLEAN 0

#define DEFAULT_SIZE 1

typedef struct array {
    size_t size;
    size_t count;
    size_t data_size;
    bool order;
    void *data;
} Array;

Array *create_array(size_t size, size_t reserved_size) {
    Array *new = (Array *)malloc(sizeof(Array));
    if (new == NULL || size == 0)
        return NULL;

    if (reserved_size == 0)
        reserved_size = DEFAULT_SIZE;

    new->data = (void *)malloc(reserved_size * size);
    if (new->data == NULL) {
        free(new);
        return NULL;
    }

    new->size = reserved_size;
    new->count = 0;
    new->data_size = size;
    new->order = true;

    return new;
}

void *destroy_array(Array *array, bool free_segment) {
    if (array == NULL)
        return NULL;

    void *temp = array->data;
    if (free_segment == true && array->data != NULL) {
        free(array->data);            
        temp = NULL;
    }

    free(array);

    return temp;
}

/**
 * @brief Calculates the load factor of the array
 * Assumes arr is not NULL
 * 
 * @param arr Array
 * @return float Load Factor
 */
static float array_load_factor(const Array *arr) {
    return (float)arr->count / (float)arr->size;
}

/**
 * @brief Allocates new space for the array, either grows ou shrinks
 * 
 * @param arr Array
 * @param change Indicates if grows or shrinks
 * @return int 1 if allocation goes wrong
 */
static int array_resize(Array *arr, int change) {
    if (change == 0)
        return 0;

    size_t new_size = 2 * arr->size;
    if (change < 0)
        new_size /= 3;

    arr->data = realloc(arr->data, new_size * arr->data_size);
    if (arr->data == NULL)
        return 1;

    arr->size = new_size;

    return 0;
}

int _array_append(Array *arr, const void *data) {
    if (arr == NULL)
        return 1;

    // array is full
    if (array_load_factor(arr) == 1) {
        if (array_resize(arr, GROW) != 0)
            return 2;
    }

    memcpy(arr->data + arr->count * arr->data_size, data, arr->data_size);
    arr->count++;

    return 0;
}

/**
 * @brief Pushs the elements on the array range positions ahead
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param count Total number of elements on the array
 * @param range Number of positions to push
 * @note This function assumes there is enough space in the array for the operation, and range > 0
 */
static void _array_push_elements(void *base, size_t size, size_t count, size_t range) {
    size_t ite = 0;
    for (ite = count - 1; ite > 0; ite--)
        memcpy(base + (ite + range) * size, base + ite * size, size);

    // ite is unsigned so goes around when less than 0
    if (ite == 0)
        memcpy(base + range * size, base, size);
}

/**
 * @brief Pulls the elements on the array range positions ahead
 * 
 * @param base Array
 * @param size Byte size of each element on the array
 * @param count Total number of elements on the array
 * @param range Number of positions to pull
 */
static void _array_pull_elements(void *base, size_t size, size_t count, size_t range) {
    for (size_t ite = range; ite < count; ite++)
        memcpy(base + (ite - range) * size, base + ite * size, size);
}

int _array_preppend(Array *arr, const void *data) {
    if (arr == NULL || arr->data == NULL)
        return 1;

    // array is full
    if (array_load_factor(arr) == 1) {
        if (array_resize(arr, GROW) != 0)
            return 2;
    }

    _array_push_elements(arr->data, arr->data_size, arr->count, 1);
    memcpy(arr->data, data, arr->data_size);
    arr->count++;

    return 0;
}

int array_pop(Array *arr, void *dest) {
    if (arr == NULL)
        return 1;

    // array is empty
    if (arr->count == 0 || arr->data == NULL)
        return 2;

    // occupation is less than 30%, so reduce to 2/3 of the original size
    if (array_load_factor(arr) < 0.3) {
        if (array_resize(arr, SHRINK) != 0)
            return 3;
    }

    arr->count--;    
    memcpy(dest, arr->data + arr->count * arr->data_size, arr->data_size);

    return 0;
}

size_t array_size(Array *arr) {
    if (arr == NULL)
        return 0;

    return arr->count;
}

int _array_insert(Array *arr, const void *data, size_t index) {
    if (arr == NULL || arr->data == NULL)
        return 1;

    // array is full
    if (array_load_factor(arr) == 1) {
        if (array_resize(arr, GROW) != 0)
            return 2;
    }

    if (index > arr->count)
        index = arr->count;
    else
        _array_push_elements(arr->data + index * arr->data_size, arr->data_size, arr->count - index, 1);
    
    memcpy(arr->data + index * arr->data_size, data, arr->data_size);
    arr->count++;

    return 0;
}

int array_remove(Array *arr, void *dest, size_t index) {
    if (arr == NULL || arr->data == NULL)
        return 1;

    if (index >= arr->count)
        index = arr->count - 1;

    memcpy(dest, arr->data + index * arr->data_size, arr->data_size);
    _array_pull_elements(arr->data + index * arr->data_size, arr->data_size, arr->count - index, 1);
    arr->count--;

    return 0;
}

void array_index(Array *arr, size_t index, void *dest) {
    if (arr == NULL || arr->data == NULL)
        return;

    if (index >= arr->count)
        index = arr->count - 1;

    memcpy(dest, arr->data + index * arr->data_size, arr->data_size);
}

void array_sort(Array *arr, int (*compare)(const void *, const void *)) {
    if (arr == NULL || arr->data == NULL || compare == NULL)
        return;

    qsort(arr->data, arr->count, arr->data_size, compare);
}

void show_array(Array *arr, void (*show)(const void *, FILE *), FILE *fp) {
    if (arr == NULL || arr->data == NULL)
        return;

    for (size_t i = 0; i < arr->count; i++)
        show(arr->data + i * arr->data_size, fp);
}