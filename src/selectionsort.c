#include "selectionsort.h"

static void swap(int *a, int *b);

void selectionsort(int arr[], size_t arr_len)
{
    /* Starting from first item in array */
    for (size_t i = 0; i < arr_len; i++)
    {
        /* Find index of min item */
        size_t min = i;
        for (size_t j = i + 1; j < arr_len; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        /* Swap min with first unsorted position */
        swap(&arr[min], &arr[i]);
    }
}

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
