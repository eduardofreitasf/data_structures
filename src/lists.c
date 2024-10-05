#include "lists.h"


typedef struct l_list {
    void *data;
    struct l_list * next;
} LList;

