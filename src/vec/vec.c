#include "vec.h"

#include <assert.h>
#include <stdlib.h>

/* These macros make make it easier to control operators' precedence without harming readability */
#define vec__data (vec->data)
#define vec__len (vec->len)
#define vec__cap (vec->cap)

struct Vec
{
    VecItem *data;
    size_t len; /* Length */
    size_t cap; /* Capacity */
};

size_t vec_len(const struct Vec *vec)
{
    return vec__len;
}

size_t vec_cap(const struct Vec *vec)
{
    return vec__cap;
}

VecItem vec_nth(const struct Vec *vec, size_t nth)
{
    if (vec__len == 0 || nth >= vec__len)
    {
        return VEC_ITEM_NONE;
    }
    return vec__data[nth];
}

struct Vec *vec_new(size_t cap)
{
    assert(cap >= 1);
    struct Vec *vec = malloc(sizeof(struct Vec));
    vec__data = malloc(cap * sizeof(VecItem));
    vec__len = 0;
    vec__cap = cap;
    return vec;
}

void vec_push(struct Vec *vec, VecItem item)
{
    /* Double capacity if it's equal to the length */
    if (vec__len >= vec__cap)
    {
        vec__cap = vec__cap * 2;
        vec__data = realloc(vec__data, vec__cap * sizeof(VecItem));
    }

    vec__data[vec__len] = item;
    vec__len++;
}

VecItem vec_pop(struct Vec *vec)
{
    if (vec__len == 0)
    {
        return VEC_ITEM_NONE;
    }

    VecItem item = vec__data[vec__len - 1];
    vec__len--;

    /* Halve capacity if it's more than double the length */
    if (vec__cap >= (2 * vec__len) && vec__len > 0)
    {
        vec__cap = vec__cap / 2;
        vec__data = realloc(vec__data, vec__cap * sizeof(VecItem));
    }
    return item;
}

VecItem vec_shift(struct Vec *vec)
{
    if (vec__len == 0)
    {
        return VEC_ITEM_NONE;
    }

    VecItem item = vec__data[0];
    vec__len--;
    for (size_t i = 0; i < vec__len; i++)
    {
        vec__data[i] = vec__data[i + 1];
    }

    /* Halve capacity if it's more than double the length */
    if (vec__cap >= (2 * vec__len) && vec__len > 0)
    {
        vec__cap = vec__cap / 2;
        vec__data = realloc(vec__data, vec__cap * sizeof(VecItem));
    }
    return item;
}

void vec_destroy(struct Vec *vec)
{
    free(vec__data);
    vec__len = 0;
    vec__cap = 0;
    free(vec);
}
