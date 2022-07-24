#include <gtest/gtest.h>

extern "C"
{
#include "binarysearch.h"
}

TEST(search, binarysearch)
{
    int arr[10] = {-21, 0, 4, 12, 19, 32, 46, 77, 90, 123};
    EXPECT_EQ(binarysearch(arr, 10, -21), 0);
    EXPECT_EQ(binarysearch(arr, 10, 46), 6);
    EXPECT_EQ(binarysearch(arr, 10, 123), 9);
    EXPECT_EQ(binarysearch(arr, 10, 8), BINARYSEARCH_IDX_NONE);
}
