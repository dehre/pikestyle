#include "htable.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define HASH_FN_MAX_RETURNED_VAL (('z' - 'a') + 1)
#define IDX_NOT_FOUND SIZE_MAX

/* These macros make make it easier to control operators' precedence without harming readability */
#define ht__data (ht->data)
#define ht__len (ht->len)
#define ht__cap (ht->cap)

struct HTable
{
    struct HTableItem *data;
    size_t len; /* Length */
    size_t cap; /* Capacity */
};

/* The fn streql compares two strings for equality, even if they're NULL */
static bool streql(const char *str1, const char *str2);

static size_t findNextItemByKey(struct HTable *ht, HTableKey key, size_t start_idx);

bool htable_itemIsNone(struct HTableItem item)
{
    return item.key == NULL;
}

size_t htable_len(struct HTable *ht)
{
    return ht == NULL ? 0 : ht__len;
}

size_t htable_cap(struct HTable *ht)
{
    return ht == NULL ? 0 : ht__cap;
}

struct HTable *htable_new(void)
{
    struct HTable *ht = malloc(sizeof(struct HTable));
    ht__data = calloc(HASH_FN_MAX_RETURNED_VAL + 1, sizeof(struct HTableItem));
    ht__len = 0;
    ht__cap = HASH_FN_MAX_RETURNED_VAL + 1;
    return ht;
}

void htable_insert(struct HTable *ht, struct HTableItem item)
{
    if (ht == NULL || ht__len >= ht__cap)
    {
        return;
    }
    assert(strlen(item.key) > 0);
    size_t start_idx = htable_hash(item.key);
    size_t idx = findNextItemByKey(ht, NULL, start_idx);
    ht__data[idx] = item;
    ht__len++;
}

struct HTableItem htable_search(struct HTable *ht, HTableKey key)
{
    if (ht == NULL)
    {
        return HTABLE_ITEM_NONE;
    }
    assert(strlen(key) > 0);
    size_t start_idx = htable_hash(key);
    size_t idx = findNextItemByKey(ht, key, start_idx);
    if (idx == IDX_NOT_FOUND)
    {
        return HTABLE_ITEM_NONE;
    }
    return ht__data[idx];
}

struct HTableItem htable_remove(struct HTable *ht, HTableKey key)
{
    if (ht == NULL)
    {
        return HTABLE_ITEM_NONE;
    }
    assert(strlen(key) > 0);
    size_t start_idx = htable_hash(key);
    size_t idx = findNextItemByKey(ht, key, start_idx);
    if (idx == IDX_NOT_FOUND)
    {
        return HTABLE_ITEM_NONE;
    }
    struct HTableItem item = ht__data[idx];
    ht__data[idx] = HTABLE_ITEM_NONE;
    ht__len--;
    return item;
}

void htable_traverse(struct HTable *ht, void (*fn)(struct HTableItem item))
{
    if (ht == NULL)
    {
        return;
    }
    for (size_t i = 0; i < ht__cap; i++)
    {
        if (!htable_itemIsNone(ht__data[i]))
        {
            fn(ht__data[i]);
        }
    }
}

void htable_destroy(struct HTable **ht_ptr)
{
    if (*ht_ptr == NULL)
    {
        return;
    }
    free((*ht_ptr)->data);
    *ht_ptr = NULL;
}

size_t htable_hash(const char *key)
{
    char initial = (char)tolower(key[0]);
    if (initial < 'a' || initial > 'z')
    {
        return HASH_FN_MAX_RETURNED_VAL;
    }
    return initial - 'a';
}

static bool streql(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return str1 == NULL && str2 == NULL;
    }
    return strcmp(str1, str2) == 0;
}

static size_t findNextItemByKey(struct HTable *ht, HTableKey key, size_t start_idx)
{
    for (size_t i = 0; i < ht__cap; i++)
    {
        size_t idx = (i + start_idx) % ht__cap;
        if (streql(ht__data[idx].key, key))
        {
            return idx;
        }
    }
    return IDX_NOT_FOUND;
}
