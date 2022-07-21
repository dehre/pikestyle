/*
 * A doubly-linked list with owned nodes.
 */

#pragma once

#include <limits.h>
#include <stddef.h>

struct LListNode;

typedef int LListItem;
#define LLIST_ITEM_NONE INT_MIN

/* Get the item from the node, without removing it */
LListItem llist_item(struct LListNode *node);

/* Get the previous node from the list, without removing it */
struct LListNode *llist_prev(struct LListNode *node);

/* Get the next node from the list, without removing it */
struct LListNode *llist_next(struct LListNode *node);

/* Get the last node of the list, without removing it */
struct LListNode *llist_tail(struct LListNode *head);

/* Get the length of the list */
size_t llist_len(struct LListNode *head);

/* Create a new doubly linked list */
struct LListNode *llist_new(LListItem item);

/* Append an item to the front of the list and update list head */
void llist_push(struct LListNode **head_ptr, LListItem item);

/* Remove a node from the front of the list and update list head */
LListItem llist_pop(struct LListNode **head_ptr);

/* Remove a node from the back of the list */
LListItem llist_shift(struct LListNode **head_ptr);

/* Call fn on each node in the list */
void llist_traverse(struct LListNode *head, void (*fn)(LListItem item));

/* Delete the list (deallocate memory for all its nodes) */
void llist_destroy(struct LListNode **head_ptr);
