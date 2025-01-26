#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct trie Trie;

Trie *create_trie(void);
void destroy_trie(Trie *trie, void (*destroy)(void *));

int trie_insert(Trie *trie, void *data, const char *key);
void *trie_remove(Trie *trie, const char *key);
void *trie_lookup(const Trie *trie, const char *key);

size_t trie_size(const Trie *trie);
bool trie_is_empty(const Trie *trie);

#endif