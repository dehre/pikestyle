#include <gtest/gtest.h>

extern "C"
{
#include "llist.h"
}

TEST(llist, llist_new)
{
    struct LListNode *head = llist_new(5);
    EXPECT_EQ(llist_prev(head), nullptr);
    EXPECT_EQ(llist_next(head), nullptr);
    EXPECT_EQ(llist_tail(head), head);
    EXPECT_EQ(llist_len(head), 1);
    llist_destroy(&head);
}

TEST(llist, llist_push)
{
    struct LListNode *head = llist_new(12);
    llist_push(&head, 24);
    llist_push(&head, 36);
    llist_push(&head, 48);
    llist_push(&head, 60);

    EXPECT_EQ(llist_len(head), 5);
    EXPECT_EQ(llist_item(head), 60);
    EXPECT_EQ(llist_prev(head), nullptr);

    struct LListNode *curr = llist_next(head);
    EXPECT_EQ(llist_item(curr), 48);
    curr = llist_next(curr);
    EXPECT_EQ(llist_item(curr), 36);
    curr = llist_next(curr);
    EXPECT_EQ(llist_item(curr), 24);
    curr = llist_next(curr);
    EXPECT_EQ(llist_item(curr), 12);
    curr = llist_next(curr);
    EXPECT_EQ(llist_item(curr), LLIST_ITEM_NONE);

    struct LListNode *tail = llist_tail(head);
    EXPECT_EQ(llist_item(tail), 12);
    EXPECT_EQ(llist_next(tail), nullptr);
    EXPECT_EQ(llist_item(llist_prev(tail)), 24);

    llist_destroy(&head);
}

TEST(llist, llist_pop)
{
    struct LListNode *head = llist_new(12);
    llist_push(&head, 24);
    llist_push(&head, 36);
    llist_push(&head, 48);
    llist_push(&head, 60);
    EXPECT_EQ(llist_len(head), 5);

    LListItem curr = llist_pop(&head);
    EXPECT_EQ(curr, 60);
    EXPECT_EQ(llist_len(head), 4);
    curr = llist_pop(&head);
    EXPECT_EQ(curr, 48);
    EXPECT_EQ(llist_len(head), 3);
    curr = llist_pop(&head);
    EXPECT_EQ(curr, 36);
    EXPECT_EQ(llist_len(head), 2);
    curr = llist_pop(&head);
    EXPECT_EQ(curr, 24);
    EXPECT_EQ(llist_len(head), 1);
    curr = llist_pop(&head);
    EXPECT_EQ(curr, 12);
    EXPECT_EQ(llist_len(head), 0);
    curr = llist_pop(&head);
    EXPECT_EQ(curr, LLIST_ITEM_NONE);
    EXPECT_EQ(llist_len(head), 0);
    EXPECT_EQ(head, nullptr);

    llist_destroy(&head);
}

TEST(llist, llist_shift)
{
    struct LListNode *head = llist_new(12);
    llist_push(&head, 24);
    llist_push(&head, 36);
    llist_push(&head, 48);
    llist_push(&head, 60);
    EXPECT_EQ(llist_len(head), 5);

    LListItem curr = llist_shift(&head);
    EXPECT_EQ(curr, 12);
    EXPECT_EQ(llist_len(head), 4);
    curr = llist_shift(&head);
    EXPECT_EQ(curr, 24);
    EXPECT_EQ(llist_len(head), 3);
    curr = llist_shift(&head);
    EXPECT_EQ(curr, 36);
    EXPECT_EQ(llist_len(head), 2);
    curr = llist_shift(&head);
    EXPECT_EQ(curr, 48);
    EXPECT_EQ(llist_len(head), 1);
    curr = llist_shift(&head);
    EXPECT_EQ(curr, 60);
    EXPECT_EQ(llist_len(head), 0);
    curr = llist_shift(&head);
    EXPECT_EQ(curr, LLIST_ITEM_NONE);
    EXPECT_EQ(llist_len(head), 0);
    EXPECT_EQ(head, nullptr);

    llist_destroy(&head);
}
