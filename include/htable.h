/*
 * Hash Table, a data structure used to store keys/value pairs.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

struct HTable;

typedef const char *HTableKey;
typedef int HTableVal;
struct HTableItem
{
    HTableKey key;
    HTableVal val;
};

#define HTABLE_ITEM_NONE ((struct HTableItem){.key = NULL})

/* Check whether an item exists */
bool htable_itemIsNone(struct HTableItem item);

/* Get the length of the hash table */
size_t htable_len(struct HTable *ht);

/* Get the capacity of the hash table */
size_t htable_cap(struct HTable *ht);

/* Create a new hash table */
struct HTable *htable_new(void);

/* Add an item to the table; the key should be a non-empty null-terminated string */
void htable_insert(struct HTable *ht, struct HTableItem item);

/* Get an item from the table, without removing it; the key should be a non-empty null-terminated string */
struct HTableItem htable_search(struct HTable *ht, HTableKey key);

/* Remove an item from the table; the key should be a non-empty null-terminated string */
struct HTableItem htable_remove(struct HTable *ht, HTableKey key);

/* Call fn on each element in the hash table */
void htable_traverse(struct HTable *ht, void (*fn)(struct HTableItem item));

/* Delete the hash table (deallocate its memory) */
void htable_destroy(struct HTable **ht);

/* Hash the key; the fn is exported for testing purposes only */
size_t htable_hash(const char *key);
