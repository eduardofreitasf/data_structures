#include "trie.h"
#include <stdlib.h>
#include <string.h>

static const char *keys = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
#define LEN (strlen(keys))

struct node {
    void *data; // NULL represents no data, just part of the path
    struct node **children;
};

typedef struct trie {
    size_t size;
    struct node *root;
} Trie;

/**
 * @brief Create a node object
 * 
 * @param data 
 * @return struct node* 
 */
static struct node *create_node(void *data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;

    new_node->children = (struct node **)malloc(LEN * sizeof(struct node *));
    if (new_node->children == NULL) {
        free(new_node);
        return NULL;
    }

    new_node->data = data;

    return new_node;
}

Trie *create_trie(void) {
    Trie *new = (Trie *)malloc(sizeof(Trie));
    if (new == NULL)
        return NULL;

    new->size = 0;
    new->root = NULL;

    return new;
}

/**
 * @brief 
 * 
 * @param root 
 * @param destroy 
 * @param size 
 */
static void clean_nodes(struct node *root, void (*destroy)(void *), size_t size) {
    if (root != NULL) {
        if (root->data != NULL)
            destroy(root->data);

        for (size_t i = 0; i < size; i++)
            clean_nodes(root->children[i], destroy, size);

        free(root);
    }
}

void destroy_trie(Trie *trie, void (*destroy)(void *)) {
    if (trie != NULL && destroy != NULL) {
        clean_nodes(trie->root, destroy, LEN);

        free(trie);
    }
}

int trie_insert(Trie *trie, void *data, const char *key) {
    if (trie == NULL || key == NULL)
        return 1;

    if (trie->root == NULL)
        trie->root = create_node(NULL);

    struct node **temp = trie->root->children;

    for (size_t i = 0, j = 0; key[i] != '\0'; i++) {
        for (j = 0; keys[j] != '\0' && keys[j] != key[i]; j++);

        if (keys[j] != '\0') {
            if (temp[j] == NULL) {
                temp[j] = create_node(NULL);
                if (temp[j] == NULL)
                    return 2;
                // end of the key
                if (key[i + 1] == '\0')
                    temp[j]->data = data;
                else
                    temp = temp[j]->children;
            } else {
                // end of the key
                if (key[i + 1] == '\0') {
                    if (temp[j]->data != NULL)
                        temp[j]->data = data;
                } else
                    temp = temp[j]->children;
            }
        }
    }

    return 0;
}


size_t trie_size(const Trie *trie) {
    if (trie != NULL)
        return trie->size;

    return 0;
}

bool trie_is_empty(const Trie *trie) {
    return trie != NULL && trie->size == 0;
}
