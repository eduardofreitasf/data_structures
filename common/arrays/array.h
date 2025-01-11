#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdbool.h>

typedef struct array Array;

Array *create_array(size_t size, size_t reserved_size);
void *destroy_array(Array *array, bool free_segment);

int _array_append(Array *arr, const void *data);
int _array_preppend(Array *arr, const void *data);

int array_pop(Array *arr, void *dest);
size_t array_size(Array *arr);
int _array_insert(Array *arr, const void *data, size_t index);
int array_remove(Array *arr, void *dest, size_t index);
void array_index(Array *arr, size_t index, void *dest);
void array_sort(Array *arr, int (*compare)(const void *, const void *));
void show_array(Array *arr, void (*show)(const void *, FILE *), FILE *fp);

#define array_append(arr, d) _array_append((arr), &(d))
#define array_preppend(arr, d) _array_preppend((arr), &(d))
#define array_insert(arr, d, i) _array_insert((arr), &(d), (i))

#endif

