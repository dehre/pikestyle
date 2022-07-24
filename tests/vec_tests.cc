#include <gtest/gtest.h>

extern "C"
{
#include "vec.h"
}

TEST(vec, vec_new)
{
    struct Vec *vec = vec_new(5);
    EXPECT_NE(vec, nullptr);
    EXPECT_EQ(vec_len(vec), 0);
    EXPECT_EQ(vec_cap(vec), 5);
    vec_destroy(&vec);
    EXPECT_EQ(vec, nullptr);
}

TEST(vec, vec_push)
{
    struct Vec *vec = vec_new(2);
    vec_push(vec, 12);
    EXPECT_EQ(vec_nth(vec, 0), 12);
    EXPECT_EQ(vec_len(vec), 1);
    EXPECT_EQ(vec_cap(vec), 2);

    vec_push(vec, 24);
    EXPECT_EQ(vec_nth(vec, 1), 24);
    EXPECT_EQ(vec_len(vec), 2);
    EXPECT_EQ(vec_cap(vec), 2);

    vec_push(vec, 36);
    EXPECT_EQ(vec_nth(vec, 2), 36);
    EXPECT_EQ(vec_len(vec), 3);
    EXPECT_EQ(vec_cap(vec), 4);
    EXPECT_EQ(vec_nth(vec, 3), VEC_ITEM_NONE);

    vec_destroy(&vec);
}

TEST(vec, vec_pop)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 12);
    vec_push(vec, 24);
    vec_push(vec, 36);
    vec_push(vec, 48);
    vec_push(vec, 60);
    EXPECT_EQ(vec_len(vec), 5);
    EXPECT_EQ(vec_cap(vec), 5);

    VecItem item;
    item = vec_pop(vec);
    EXPECT_EQ(item, 60);
    EXPECT_EQ(vec_len(vec), 4);
    EXPECT_EQ(vec_cap(vec), 5);

    item = vec_pop(vec);
    EXPECT_EQ(item, 48);
    EXPECT_EQ(vec_len(vec), 3);
    EXPECT_EQ(vec_cap(vec), 5);

    item = vec_pop(vec);
    EXPECT_EQ(item, 36);
    EXPECT_EQ(vec_len(vec), 2);
    EXPECT_EQ(vec_cap(vec), 2);

    item = vec_pop(vec);
    EXPECT_EQ(item, 24);
    EXPECT_EQ(vec_len(vec), 1);
    EXPECT_EQ(vec_cap(vec), 1);

    item = vec_pop(vec);
    EXPECT_EQ(item, 12);
    EXPECT_EQ(vec_len(vec), 0);
    EXPECT_EQ(vec_cap(vec), 1);

    item = vec_pop(vec);
    EXPECT_EQ(item, VEC_ITEM_NONE);
    EXPECT_EQ(vec_len(vec), 0);
    EXPECT_EQ(vec_cap(vec), 1);

    vec_destroy(&vec);
}

TEST(vec, vec_shift)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 12);
    vec_push(vec, 24);
    vec_push(vec, 36);
    vec_push(vec, 48);
    vec_push(vec, 60);
    EXPECT_EQ(vec_len(vec), 5);
    EXPECT_EQ(vec_cap(vec), 5);

    VecItem item;
    item = vec_shift(vec);
    EXPECT_EQ(item, 12);
    EXPECT_EQ(vec_len(vec), 4);
    EXPECT_EQ(vec_cap(vec), 5);

    item = vec_shift(vec);
    EXPECT_EQ(item, 24);
    EXPECT_EQ(vec_len(vec), 3);
    EXPECT_EQ(vec_cap(vec), 5);

    item = vec_shift(vec);
    EXPECT_EQ(item, 36);
    EXPECT_EQ(vec_len(vec), 2);
    EXPECT_EQ(vec_cap(vec), 2);

    item = vec_shift(vec);
    EXPECT_EQ(item, 48);
    EXPECT_EQ(vec_len(vec), 1);
    EXPECT_EQ(vec_cap(vec), 1);

    item = vec_shift(vec);
    EXPECT_EQ(item, 60);
    EXPECT_EQ(vec_len(vec), 0);
    EXPECT_EQ(vec_cap(vec), 1);

    item = vec_shift(vec);
    EXPECT_EQ(item, VEC_ITEM_NONE);
    EXPECT_EQ(vec_len(vec), 0);
    EXPECT_EQ(vec_cap(vec), 1);

    vec_destroy(&vec);
}

static unsigned int mockCallbackCalledTimes = 0;
static VecItem mockCallbackCalledWith[5] = {0};
void mockCallback(VecItem item)
{
    mockCallbackCalledWith[mockCallbackCalledTimes++] = item;
}
TEST(vec, vec_traverse)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 12);
    vec_push(vec, 24);
    vec_push(vec, 36);
    vec_push(vec, 48);
    vec_push(vec, 60);
    EXPECT_EQ(vec_len(vec), 5);

    vec_traverse(vec, mockCallback);
    EXPECT_EQ(mockCallbackCalledTimes, 5);
    EXPECT_EQ(mockCallbackCalledWith[0], 12);
    EXPECT_EQ(mockCallbackCalledWith[1], 24);
    EXPECT_EQ(mockCallbackCalledWith[2], 36);
    EXPECT_EQ(mockCallbackCalledWith[3], 48);
    EXPECT_EQ(mockCallbackCalledWith[4], 60);

    vec_destroy(&vec);
}

TEST(vec, vec_sort)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 48);
    vec_push(vec, 24);
    vec_push(vec, 60);
    vec_push(vec, 12);
    vec_push(vec, 36);

    vec_sort(vec);
    EXPECT_EQ(vec_nth(vec, 0), 12);
    EXPECT_EQ(vec_nth(vec, 1), 24);
    EXPECT_EQ(vec_nth(vec, 2), 36);
    EXPECT_EQ(vec_nth(vec, 3), 48);
    EXPECT_EQ(vec_nth(vec, 4), 60);

    vec_destroy(&vec);
}

TEST(vec, vec_search)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 48);
    vec_push(vec, 24);
    vec_push(vec, 60);
    vec_push(vec, 12);
    vec_push(vec, 36);

    EXPECT_EQ(vec_search(vec, 48), 0);
    EXPECT_EQ(vec_search(vec, 60), 2);
    EXPECT_EQ(vec_search(vec, 36), 4);
    EXPECT_EQ(vec_search(vec, 17), SEARCH_IDX_NONE);

    vec_destroy(&vec);
}

TEST(vec, vec_binarysearch)
{
    struct Vec *vec = vec_new(5);
    vec_push(vec, 12);
    vec_push(vec, 24);
    vec_push(vec, 36);
    vec_push(vec, 48);
    vec_push(vec, 60);

    EXPECT_EQ(vec_binarysearch(vec, 12), 0);
    EXPECT_EQ(vec_binarysearch(vec, 36), 2);
    EXPECT_EQ(vec_binarysearch(vec, 60), 4);
    EXPECT_EQ(vec_binarysearch(vec, 17), SEARCH_IDX_NONE);

    vec_destroy(&vec);
}
