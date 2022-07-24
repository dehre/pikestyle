#include "quicksort.h"

void quicksort_easy(int arr[], size_t arr_len)
{
    if (arr_len < 2) /* an arr with len 0 or 1 is sorted already */
    {
        return;
    }

    int pivot = arr[0];
    int less_than_pivot[arr_len];
    int greater_than_pivot[arr_len];
    size_t less_than_pivot_len = 0;
    size_t greater_than_pivot_len = 0;
    for (size_t i = 1; i < arr_len; i++)
    {
        int curr = arr[i];
        if (curr < pivot)
        {
            less_than_pivot[less_than_pivot_len++] = curr;
        }
        if (curr > pivot)
        {
            greater_than_pivot[greater_than_pivot_len++] = curr;
        }
    }
    quicksort_easy(less_than_pivot, less_than_pivot_len);
    quicksort_easy(greater_than_pivot, greater_than_pivot_len);

    size_t arr_idx = 0;
    for (size_t i = 0; i < less_than_pivot_len; i++)
    {
        arr[arr_idx++] = less_than_pivot[i];
    }
    arr[arr_idx++] = pivot;
    for (size_t i = 0; i < greater_than_pivot_len; i++)
    {
        arr[arr_idx++] = greater_than_pivot[i];
    }
}
