#pragma once

#include <limits.h>

struct BSTNode;

typedef int BSTItem;
#define BST_ITEM_NONE INT_MIN

/* Get the item from the node, without removing it */
BSTItem bst_item(struct BSTNode *node);

/* Get the previous node from the list, without removing it */
struct BSTNode *bst_left(struct BSTNode *node);

/* Get the next node from the list, without removing it */
struct BSTNode *bst_right(struct BSTNode *node);

/* Create a new binary search tree */
struct BSTNode *bst_new(BSTItem item);

/* Add an item to the tree; the fn returns root */
struct BSTNode *bst_insert(struct BSTNode *root, BSTItem item);

/* Get an item from the tree, without removing it */
struct BSTNode *bst_search(struct BSTNode *root, BSTItem item);

/* Remove an item from the tree; the fn returns the new root */
struct BSTNode *bst_remove(struct BSTNode *root, BSTItem item);

// TODO LORIS: implementation
/* Balance the tree */
void bst_balance(struct BSTNode **root);

// TODO LORIS: implementation
/* Call fn on each element in the tree */
void bst_traverse(struct BSTNode *root, void *(*fn)(BSTItem item));

/* Delete the binary search tree (deallocate its memory) */
void bst_destroy(struct BSTNode **root);
