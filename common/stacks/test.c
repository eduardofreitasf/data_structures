#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct test {
    char *name;
    unsigned age;
};

void test_destroy(void *ptr) {
    if (ptr != NULL) {
        struct test *temp = (struct test *)ptr;
        if (temp->name != NULL)
            free(temp->name);

        free(temp);
    }
}

struct test *test_create(char *name, unsigned age) {
    struct test *new = (struct test *)malloc(sizeof(struct test));
    if (new == NULL)
        return NULL;

    *new = (struct test){.name = name, .age = age};

    return new;
}

unsigned random_int(unsigned limit) { return rand() % limit; }

char *random_string(size_t size) {
    const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t charsetSize = sizeof(charset) - 1; // Exclude the null terminator

    // Allocate memory for the random string (+1 for the null terminator)
    char *output = (char *)malloc((size + 1) * sizeof(char));
    if (output == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate the random string
    for (size_t i = 0; i < size; i++)
        output[i] = charset[rand() % charsetSize];

    // Null-terminate the string
    output[size] = '\0';

    return output;
}

int main(int argc, char **argv) { return 0; }
