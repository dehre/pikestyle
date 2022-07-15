#include <gtest/gtest.h>

extern "C"
{
#include "modern.h"
}

TEST(Modern, ReverseInPlace)
{
    char str_a[] = "hello";
    EXPECT_STREQ(reverse_in_place(str_a), "olleh");

    char str_b[] = "Hello world!";
    EXPECT_STREQ(reverse_in_place(str_b), "!dlrow olleH");
}
