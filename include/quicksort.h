#pragma once

#include <stddef.h>

void quicksort(int arr[], int low_idx, int high_idx);

/* An easier to read but less space efficient implementation of quicksort */
void quicksort_easy(int arr[], size_t arr_len);
