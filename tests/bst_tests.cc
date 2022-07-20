#include <gtest/gtest.h>

extern "C"
{
#include "bst.h"
}

TEST(bst, bst_new)
{
    struct BSTNode *root = bst_new(12);
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(bst_item(root), 12);
    EXPECT_EQ(bst_left(root), nullptr);
    EXPECT_EQ(bst_right(root), nullptr);

    bst_destroy(&root);
    EXPECT_EQ(root, nullptr);
}

TEST(bst, bst_insert)
{
    struct BSTNode *root = bst_new(12);
    struct BSTNode *newNode;

    bst_insert(root, 6);
    EXPECT_EQ(bst_right(root), nullptr);
    newNode = bst_left(root);
    EXPECT_NE(newNode, nullptr);
    EXPECT_EQ(bst_item(newNode), 6);
    EXPECT_EQ(bst_left(newNode), nullptr);
    EXPECT_EQ(bst_right(newNode), nullptr);

    bst_insert(root, 18);
    newNode = bst_right(root);
    EXPECT_NE(newNode, nullptr);
    EXPECT_EQ(bst_item(newNode), 18);
    EXPECT_EQ(bst_left(newNode), nullptr);
    EXPECT_EQ(bst_right(newNode), nullptr);

    bst_destroy(&root);
}

TEST(bst, bst_search)
{
    struct BSTNode *root = bst_new(36);
    bst_insert(root, 6);
    bst_insert(root, 12);
    bst_insert(root, 24);
    bst_insert(root, 60);
    bst_insert(root, 48);
    bst_insert(root, 44);

    EXPECT_EQ(bst_item(root), 36);
    EXPECT_EQ(bst_item(bst_left(root)), 6);
    EXPECT_EQ(bst_item(bst_right(root)), 60);

    EXPECT_EQ(bst_item(bst_search(root, 12)), 12);
    EXPECT_EQ(bst_item(bst_right(bst_search(root, 12))), 24);

    EXPECT_EQ(bst_item(bst_search(root, 48)), 48);
    EXPECT_EQ(bst_item(bst_left(bst_search(root, 48))), 44);

    EXPECT_EQ(bst_item(bst_search(root, 55)), BST_ITEM_NONE);

    bst_destroy(&root);
}

TEST(bst, bst_remove)
{
    struct BSTNode *root = bst_new(36);
    bst_insert(root, 6);
    bst_insert(root, 12);
    bst_insert(root, 24);
    bst_insert(root, 60);
    bst_insert(root, 48);
    bst_insert(root, 44);

    EXPECT_EQ(bst_item(root), 36);
    EXPECT_EQ(bst_item(bst_left(root)), 6);
    EXPECT_EQ(bst_item(bst_right(root)), 60);

    root = bst_remove(root, 12);
    EXPECT_EQ(bst_item(bst_search(root, 12)), BST_ITEM_NONE);
    EXPECT_EQ(bst_item(bst_right(bst_search(root, 6))), 24);

    root = bst_remove(root, 60);
    EXPECT_EQ(bst_item(bst_search(root, 60)), BST_ITEM_NONE);
    EXPECT_EQ(bst_item(bst_right(root)), 48);

    /* Should not segfault when removing non-existent items */
    EXPECT_EQ(bst_item(bst_remove(root, 55)), bst_item(root));

    root = bst_remove(root, 36);
    EXPECT_EQ(bst_item(bst_search(root, 36)), BST_ITEM_NONE);
    EXPECT_EQ(bst_item(root), 44);

    bst_destroy(&root);
}
