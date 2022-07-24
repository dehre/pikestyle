#include "binarysearch.h"

size_t binarysearch(const int arr[], size_t arr_len, int x)
{
    size_t low_idx = 0;
    size_t high_idx = arr_len - 1;
    while (low_idx <= high_idx)
    {
        size_t mid_idx = (high_idx + low_idx) / 2;
        int guess = arr[mid_idx];
        if (guess == x)
        {
            return mid_idx;
        }
        if (guess < x)
        {
            low_idx = mid_idx + 1;
        }
        if (guess > x)
        {
            high_idx = mid_idx - 1;
        }
    }
    return SEARCH_IDX_NONE;
}
