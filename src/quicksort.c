#include "quicksort.h"

static int partition(int arr[], int low_idx, int high_idx);
static void swap(int *a, int *b);

// TODO LORIS: use size_t for indexes, and partition from right to left of the array
// TODO LORIS: remove type casting in vec.c
void quicksort(int arr[], int low_idx, int high_idx)
{
    if (low_idx < high_idx)
    {
        /* Items on the left of pivot will be smaller, items on the right will be bigger */
        int pivot_idx = partition(arr, low_idx, high_idx);
        quicksort(arr, low_idx, pivot_idx - 1);
        quicksort(arr, pivot_idx + 1, high_idx);
    }
}

static int partition(int arr[], int low_idx, int high_idx)
{
    int pivot = arr[high_idx];

    /* This index moves towards the right of the array, so that items
     * at index <= pivot_final_idx are smaller than pivot */
    int pivot_final_idx = (low_idx - 1);

    for (int i = low_idx; i < high_idx; i++)
    {
        if (arr[i] <= pivot)
        {
            pivot_final_idx++;
            swap(&(arr[i]), &(arr[pivot_final_idx]));
        }
    }

    pivot_final_idx++;
    swap(&(arr[high_idx]), &(arr[pivot_final_idx]));
    return pivot_final_idx;
}

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
