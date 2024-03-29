#include "llist.h"

#include <stdlib.h>

struct LListNode
{
    LListItem item;
    struct LListNode *prev;
    struct LListNode *next;
};

static LListItem drainNode(struct LListNode *node);

LListItem llist_item(const struct LListNode *node)
{
    if (node == NULL)
    {
        return LLIST_ITEM_NONE;
    }
    return node->item;
}

struct LListNode *llist_prev(struct LListNode *node)
{
    return node->prev;
}

struct LListNode *llist_next(struct LListNode *node)
{
    return node->next;
}

struct LListNode *llist_tail(struct LListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    struct LListNode *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    return curr;
}

size_t llist_len(const struct LListNode *head)
{
    size_t count = 0;
    if (head == NULL)
    {
        return count;
    }
    const struct LListNode *curr = head;
    do
    {
        curr = curr->next;
        count++;
    } while (curr != NULL);
    return count;
}

struct LListNode *llist_new(LListItem item)
{
    struct LListNode *node = malloc(sizeof(struct LListNode));
    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void llist_push(struct LListNode **head_ptr, LListItem item)
{
    struct LListNode *new_node = llist_new(item);
    if (*head_ptr == NULL)
    {
        *head_ptr = new_node;
        return;
    }
    struct LListNode *old_head = *head_ptr;
    new_node->next = old_head;
    old_head->prev = new_node;
    *head_ptr = new_node;
}

LListItem llist_pop(struct LListNode **head_ptr)
{
    if (*head_ptr == NULL)
    {
        return LLIST_ITEM_NONE;
    }
    struct LListNode *old_head = *head_ptr;
    *head_ptr = old_head->next;
    return drainNode(old_head);
}

LListItem llist_shift(struct LListNode **head_ptr)
{
    if (*head_ptr == NULL)
    {
        return LLIST_ITEM_NONE;
    }
    struct LListNode *tail = llist_tail(*head_ptr);
    if (tail == *head_ptr)
    {
        *head_ptr = NULL;
        return drainNode(tail);
    }
    tail->prev->next = NULL;
    return drainNode(tail);
}

void llist_traverse(const struct LListNode *head, void (*fn)(LListItem item))
{
    if (head == NULL)
    {
        return;
    }
    const struct LListNode *curr = head;
    do
    {
        fn(llist_item(curr));
        curr = curr->next;
    } while (curr != NULL);
}

void llist_destroy(struct LListNode **head_ptr)
{
    struct LListNode *curr = *head_ptr;
    while (curr != NULL)
    {
        struct LListNode *next = curr->next;
        free(curr);
        curr = next;
    }
    *head_ptr = NULL;
}

static LListItem drainNode(struct LListNode *node)
{
    LListItem item = node->item;
    free(node);
    return item;
}
