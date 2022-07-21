/*
 * Vector, a contiguous growable array type with heap-allocated contents.
 */

#pragma once

#include <limits.h>
#include <stddef.h>

struct Vec;

typedef int VecItem;
#define VEC_ITEM_NONE INT_MIN

/* Get the length of the vector */
size_t vec_len(const struct Vec *vec);

/* Get the capacity of the vector */
size_t vec_cap(const struct Vec *vec);

/* Get the nth item from the vector, without removing it */
VecItem vec_nth(const struct Vec *vec, size_t nth);

/* Create a new vector; capacity should be at least 1 */
struct Vec *vec_new(size_t cap);

/* Append an item to the back of the vector */
void vec_push(struct Vec *vec, VecItem item);

/* Remove an element from the back of the vector */
VecItem vec_pop(struct Vec *vec);

/* Remove an element from the front of the vector */
VecItem vec_shift(struct Vec *vec);

/* Call fn on each item in the vector */
void vec_traverse(struct Vec *vec, void (*fn)(VecItem item));

/* Delete the vector (deallocate its memory) */
void vec_destroy(struct Vec **vec);
