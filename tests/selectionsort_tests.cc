#include <gtest/gtest.h>

extern "C"
{
#include "selectionsort.h"
}

TEST(sort, selectionsort)
{
    int arr[10] = {77, 12, 4, 32, 46, 90, -21, 123, 0, 19};
    selectionsort(arr, 10);
    EXPECT_EQ(arr[0], -21);
    EXPECT_EQ(arr[1], 0);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 12);
    EXPECT_EQ(arr[4], 19);
    EXPECT_EQ(arr[5], 32);
    EXPECT_EQ(arr[6], 46);
    EXPECT_EQ(arr[7], 77);
    EXPECT_EQ(arr[8], 90);
    EXPECT_EQ(arr[9], 123);
}
