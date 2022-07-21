#include <gtest/gtest.h>

extern "C"
{
#include "htable.h"
}

TEST(htable, htable_hash)
{
    EXPECT_EQ(htable_hash("All"), 0);
    EXPECT_EQ(htable_hash("all"), 0);
    EXPECT_EQ(htable_hash("Hello"), 'h' - 'a');
    EXPECT_EQ(htable_hash("hello"), 'h' - 'a');
    EXPECT_EQ(htable_hash("Zebec"), 'z' - 'a');
    EXPECT_EQ(htable_hash("zebec"), 'z' - 'a');
    EXPECT_EQ(htable_hash("?what"), ('z' - 'a') + 1);
}

TEST(htable, htable_itemIsNone)
{
    EXPECT_EQ(htable_itemIsNone(HTABLE_ITEM_NONE), true);
    EXPECT_EQ(htable_itemIsNone((struct HTableItem){.key = "apples", .val = 5}), false);
}

TEST(htable, htable_insert)
{
    struct HTable *ht = htable_new();
    htable_insert(ht, (struct HTableItem){.key = "apples", .val = 5});
    EXPECT_EQ(htable_len(ht), 1);

    htable_insert(ht, (struct HTableItem){.key = "ORANGES", .val = 12});
    EXPECT_EQ(htable_len(ht), 2);

    htable_insert(ht, (struct HTableItem){.key = "olives", .val = 23});
    EXPECT_EQ(htable_len(ht), 3);

    htable_insert(ht, (struct HTableItem){.key = "!guests", .val = 3});
    EXPECT_EQ(htable_len(ht), 4);

    htable_insert(ht, (struct HTableItem){.key = "%@whatsthat@", .val = 3});
    EXPECT_EQ(htable_len(ht), 5);

    htable_destroy(&ht);
    EXPECT_EQ(ht, nullptr);
}

TEST(htable, htable_search)
{
    struct HTable *ht = htable_new();
    htable_insert(ht, (struct HTableItem){.key = "apples", .val = 5});
    htable_insert(ht, (struct HTableItem){.key = "ORANGES", .val = 12});
    htable_insert(ht, (struct HTableItem){.key = "olives", .val = 23});
    htable_insert(ht, (struct HTableItem){.key = "!guests", .val = 3});
    htable_insert(ht, (struct HTableItem){.key = "%@whatsthat@", .val = 3});
    EXPECT_EQ(htable_len(ht), 5);

    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "apples")), false);
    EXPECT_EQ(htable_search(ht, "apples").val, 5);
    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "Apples")), true);

    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "ORANGES")), false);
    EXPECT_EQ(htable_search(ht, "ORANGES").val, 12);

    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "olives")), false);
    EXPECT_EQ(htable_search(ht, "olives").val, 23);

    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "!guests")), false);
    EXPECT_EQ(htable_search(ht, "!guests").val, 3);

    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "%@whatsthat@")), false);
    EXPECT_EQ(htable_search(ht, "%@whatsthat@").val, 3);
    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "%@wHaTsThAt")), true);
    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "@whatsthat@")), true);

    EXPECT_EQ(htable_len(ht), 5);
    htable_destroy(&ht);
}

TEST(htable, htable_remove)
{
    struct HTable *ht = htable_new();
    htable_insert(ht, (struct HTableItem){.key = "apples", .val = 5});
    htable_insert(ht, (struct HTableItem){.key = "ORANGES", .val = 12});
    htable_insert(ht, (struct HTableItem){.key = "olives", .val = 23});
    htable_insert(ht, (struct HTableItem){.key = "!guests", .val = 3});
    htable_insert(ht, (struct HTableItem){.key = "%@whatsthat@", .val = 3});
    EXPECT_EQ(htable_len(ht), 5);

    EXPECT_EQ(htable_itemIsNone(htable_remove(ht, "bananas")), true);

    EXPECT_EQ(htable_remove(ht, "!guests").val, 3);
    EXPECT_EQ(htable_len(ht), 4);
    EXPECT_EQ(htable_itemIsNone(htable_remove(ht, "!guests")), true);
    EXPECT_EQ(htable_len(ht), 4);

    EXPECT_EQ(htable_remove(ht, "olives").val, 23);
    EXPECT_EQ(htable_len(ht), 3);
    EXPECT_EQ(htable_itemIsNone(htable_search(ht, "olives")), true);

    EXPECT_EQ(htable_itemIsNone(htable_remove(ht, "@whatsthat@")), true);
    EXPECT_EQ(htable_len(ht), 3);
    EXPECT_EQ(htable_remove(ht, "%@whatsthat@").val, 3);
    EXPECT_EQ(htable_len(ht), 2);

    EXPECT_EQ(htable_remove(ht, "apples").val, 5);
    EXPECT_EQ(htable_remove(ht, "ORANGES").val, 12);

    EXPECT_EQ(htable_len(ht), 0);
    htable_destroy(&ht);
}

static unsigned int mockCallbackCalledTimes = 0;
static HTableItem mockCallbackCalledWith[5] = {0};
void mockCallback(HTableItem item)
{
    mockCallbackCalledWith[mockCallbackCalledTimes++] = item;
}
TEST(htable, htable_traverse)
{
    struct HTable *ht = htable_new();
    htable_insert(ht, (struct HTableItem){.key = "a", .val = 12});
    htable_insert(ht, (struct HTableItem){.key = "b", .val = 24});
    htable_insert(ht, (struct HTableItem){.key = "c", .val = 36});
    htable_insert(ht, (struct HTableItem){.key = "d", .val = 48});
    htable_insert(ht, (struct HTableItem){.key = "e", .val = 60});
    EXPECT_EQ(htable_len(ht), 5);

    htable_traverse(ht, mockCallback);
    EXPECT_EQ(mockCallbackCalledTimes, 5);
    EXPECT_EQ(mockCallbackCalledWith[0].val, 12);
    EXPECT_EQ(mockCallbackCalledWith[1].val, 24);
    EXPECT_EQ(mockCallbackCalledWith[2].val, 36);
    EXPECT_EQ(mockCallbackCalledWith[3].val, 48);
    EXPECT_EQ(mockCallbackCalledWith[4].val, 60);

    htable_destroy(&ht);
}
