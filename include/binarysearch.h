#pragma once

#include <stddef.h>
#include <stdint.h>

#define BINARYSEARCH_IDX_NONE SIZE_MAX

/* Binary search through a sorted array.
 * The fn returns the index of x in arr, or BINARYSEARCH_IDX_NONE */
size_t binarysearch(const int arr[], size_t arr_len, int x);
