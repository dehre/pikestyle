#include "bst.h"

#include <assert.h>
#include <stdlib.h>

struct BSTNode
{
    BSTItem item;
    struct BSTNode *left;
    struct BSTNode *right;
};

static struct BSTNode *findNodeWithMinItem(struct BSTNode *root);

BSTItem bst_item(struct BSTNode *node)
{
    if (node == NULL)
    {
        return BST_ITEM_NONE;
    }
    return node->item;
}

struct BSTNode *bst_left(struct BSTNode *node)
{
    return node->left;
}

struct BSTNode *bst_right(struct BSTNode *node)
{
    return node->right;
}

struct BSTNode *bst_new(BSTItem item)
{
    struct BSTNode *node = malloc(sizeof(struct BSTNode));
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct BSTNode *bst_insert(struct BSTNode *root, BSTItem item)
{
    if (root == NULL)
    {
        return bst_new(item);
    }
    if (item < root->item)
    {
        root->left = bst_insert(root->left, item);
    }
    if (item > root->item)
    {
        root->right = bst_insert(root->right, item);
    }
    return root;
}

struct BSTNode *bst_search(struct BSTNode *root, BSTItem item)
{
    if (root == NULL || item == root->item)
    {
        return root;
    }
    if (item < root->item)
    {
        return bst_search(root->left, item);
    }
    if (item > root->item)
    {
        return bst_search(root->right, item);
    }
    assert(0);
}

struct BSTNode *bst_remove(struct BSTNode *root, BSTItem item)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (item < root->item)
    {
        root->left = bst_remove(root->left, item);
        return root;
    }
    if (item > root->item)
    {
        root->right = bst_remove(root->right, item);
        return root;
    }

    /*
     * Node found!
     */

    /* No children? Simply delete the node */
    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }
    /* One child? Replace the node with its child */
    if (root->left == NULL || root->right == NULL)
    {
        struct BSTNode *replacement = root->left ? root->left : root->right;
        free(root);
        return replacement;
    }
    /* Two children? Find the node with the closest greater value and move it up to replace root */
    struct BSTNode *replacement = findNodeWithMinItem(root->right);
    root->item = replacement->item;
    root->right = bst_remove(root->right, replacement->item);
    return root;
}

// TODO LORIS: mock the free fn and expect it to be called n times?
void bst_destroy(struct BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        bst_destroy(root->left);
    }
    if (root->right != NULL)
    {
        bst_destroy(root->right);
    }
    free(root);
}

static struct BSTNode *findNodeWithMinItem(struct BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->left == NULL)
    {
        return root;
    }
    return findNodeWithMinItem(root->left);
}
