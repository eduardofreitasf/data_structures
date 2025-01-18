#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct list List;

// done and working
List *list_create(void);
// done and working
void list_destroy(List *list, void (*destroy)(void *));

// done and working
int list_append(List *list, void *data);
// done and working
int list_preppend(List *list, void *data);

// done and working
size_t list_size(const List *list);
// done and working
bool list_is_empty(const List *list);
// done and working
bool list_order(const List *list, int (*compare)(const void *, const void *));

// done and working
int list_insert(List *list, void *data, int (*compare)(const void *, const void *));
// done and working
void *list_remove(List *list, const void *key, int (*compare)(const void *, const void *));

// done and working
List *list_clone(List *list, void *(*clone)(const void *));
// done and working
void list_reverse(List *list);

// done and working
void *list_min(List *list, int (*compare)(const void *, const void *));
// done and working
void *list_max(List *list, int (*compare)(const void *, const void *));

// done and working
List *list_take(List *list, size_t size);
// done and working
List *list_drop(List *list, size_t size);

// done and working
List *list_concat(List *list1, List *list2);

// done and working
List *list_merge(List *list1, List *list2, int (*compare)(const void *, const void *));
// done and working
void list_sort(List *list, int (*compare)(const void *, const void *));

// done and working
void show_list(List *list, void (*show)(const void *, FILE *), FILE *fp);

#endif
