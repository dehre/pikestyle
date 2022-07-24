#include "bst.h"

#include "vec.h"
#include <assert.h>
#include <stdlib.h>

struct BSTNode
{
    BSTItem item;
    struct BSTNode *left;
    struct BSTNode *right;
};

/* Find the node with minimum item; the fn is used by bst_remove */
static struct BSTNode *findNodeWithMinItem(struct BSTNode *root);

/* A vector of sorted items; the var and fn are used by bst_balance (they wouldn't be needed if C allowed closures) */
static struct Vec *sortedItemsVec = NULL;
static void sortedItemsVec_push(VecItem item);

/* Create a new balanced tree recursively from a sorted vector of items; the fn is used by bst_balance */
static struct BSTNode *newBSTFromSortedVec(struct Vec *vec, size_t lower_idx, size_t upper_idx);

BSTItem bst_item(const struct BSTNode *node)
{
    return node == NULL ? BST_ITEM_NONE : node->item;
}

struct BSTNode *bst_left(struct BSTNode *node)
{
    return node == NULL ? NULL : node->left;
}

struct BSTNode *bst_right(struct BSTNode *node)
{
    return node == NULL ? NULL : node->right;
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

void bst_traverse(const struct BSTNode *root, void (*fn)(BSTItem item))
{
    if (root == NULL)
    {
        return;
    }
    bst_traverse(root->left, fn);
    fn(bst_item(root));
    bst_traverse(root->right, fn);
}

void bst_destroy(struct BSTNode **root_ptr)
{
    if (*root_ptr == NULL)
    {
        return;
    }
    bst_destroy(&((*root_ptr)->left));
    bst_destroy(&((*root_ptr)->right));
    free(*root_ptr);
    *root_ptr = NULL;
}

void bst_balance(struct BSTNode **root_ptr)
{
    sortedItemsVec = vec_new(8);
    bst_traverse(*root_ptr, sortedItemsVec_push);
    struct BSTNode *new_root = newBSTFromSortedVec(sortedItemsVec, 0, vec_len(sortedItemsVec) - 1);
    vec_destroy(&sortedItemsVec);
    bst_destroy(root_ptr);
    *root_ptr = new_root;
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

static void sortedItemsVec_push(VecItem item)
{
    vec_push(sortedItemsVec, item);
}

static struct BSTNode *newBSTFromSortedVec(struct Vec *vec, size_t lower_idx, size_t upper_idx)
{
    assert(vec != NULL);
    size_t size = upper_idx - lower_idx + 1;
    if (size == 0)
    {
        return NULL;
    }
    size_t mid_idx = size / 2 + lower_idx;
    struct BSTNode *subtree_root = bst_new(vec_nth(vec, mid_idx));
    subtree_root->left = newBSTFromSortedVec(vec, lower_idx, mid_idx - 1);
    subtree_root->right = newBSTFromSortedVec(vec, mid_idx + 1, upper_idx);
    return subtree_root;
}
