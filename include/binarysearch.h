#pragma once

#include <stddef.h>
#include <stdint.h>

#define SEARCH_IDX_NONE SIZE_MAX

/* Binary search a sorted array; the fn returns the index of x in arr, or SEARCH_IDX_NONE */
size_t binarysearch(const int arr[], size_t arr_len, int x);
