/*
 * LICENSE...
 */

#include "util_doubly_linked_list.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

struct util_node
{
  byte *data;
  size_t size;
  struct util_node *next;
  struct util_node *prev;
};

static struct util_node *
_util_node_new (const char *data, size_t size, struct util_node *next,
                struct util_node *prev)
{
  struct util_node *node = (struct util_node *)malloc (sizeof (*node));

  node->data = (byte *)malloc (size);
  memcpy (node->data, data, size);
  node->size = size;
  node->next = next;
  node->prev = prev;

  return node;
}

static struct util_node *
_util_node_get (struct util_doubly_linked_list *list, size_t idx)
{
  struct util_node *cur;
  size_t mid;
  size_t i;

  mid = list->size >> 2;
  if (idx > mid)
    {
      cur = list->last;

      for (i = list->size; i != idx; --i)
        cur = cur->prev;
    }
  else
    {
      cur = list->first;

      for (i = 0; i != idx; ++i)
        cur = cur->next;
    }
  return cur;
}

struct util_doubly_linked_list
util_doubly_linked_list_new (void)
{
  return (struct util_doubly_linked_list){ NULL, NULL, 0, 0 };
}

void
util_doubly_linked_list_push (struct util_doubly_linked_list *list,
                              const void *data, size_t size)
{
  if (!list->last)
    {
      list->last = _util_node_new (data, size, NULL, list->last);
      list->first = list->last;
    }
  else
    {
      list->last->next = _util_node_new (data, size, NULL, list->last);
      list->last = list->last->next;
    }
  list->size++;
}

void
util_doubly_linked_list_prepend (struct util_doubly_linked_list *list,
                                 const void *data, size_t size)
{
  if (!list->first)
    {
      list->first = _util_node_new (data, size, list->first, NULL);
      list->last = list->first;
    }
  else
    {
      list->first->prev = _util_node_new (data, size, list->first, NULL);
      list->first = list->first->prev;
    }
  list->size++;
}

void
util_doubly_linked_list_insert (struct util_doubly_linked_list *list,
                                size_t idx, const void *data, size_t size)
{
  if (idx > list->size) /* insert at end. */
    util_doubly_linked_list_push (list, data, size);
  else if (idx <= 0) /* insert at start. */
    util_doubly_linked_list_prepend (list, data, size);
  else /* insert at middle. */
    {
      struct util_node *cur = _util_node_get (list, idx);
      struct util_node *node = _util_node_new (data, size, cur, cur->prev);

      cur->prev->next = node;
      cur->prev = node;
      list->size++;
    }
}

void *
util_doubly_linked_list_pop (struct util_doubly_linked_list *list)
{
  struct util_node *const head = list->last;

  if (head)
    {
      void *result = head->data;

      if (head->prev)
        list->last = head->prev;
      free (head);
      list->last->next = NULL;

      if (!--list->size)
        list->first = list->last = NULL;

      return result;
    }
  return NULL;
}

void *
util_doubly_linked_list_dequeue (struct util_doubly_linked_list *list)
{
  struct util_node *const head = list->first;

  if (head)
    {
      void *result = head->data;

      if (head->next)
        list->first = head->next;
      free (head);
      list->first->prev = NULL;

      if (!--list->size)
        list->first = list->last = NULL;

      return result;
    }
  return NULL;
}

void *
util_doubly_linked_list_remove (struct util_doubly_linked_list *list,
                                size_t idx)
{
  if (idx > list->size)
    util_doubly_linked_list_pop (list);
  else if (idx <= 0)
    util_doubly_linked_list_dequeue (list);
  else
    {
      struct util_node *cur = _util_node_get (list, idx);
      void *result = cur->data;

      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
      free (cur);
      list->size--;

      return result;
    }
  return NULL;
}

void
util_doubly_linked_list_delete (struct util_doubly_linked_list *list)
{
  while (list->first)
    {
      free (util_doubly_linked_list_pop (list));
    }
}

void *
util_doubly_linked_list_get_first (struct util_doubly_linked_list *list)
{
  return list->first->data;
}

void *
util_doubly_linked_list_get_last (struct util_doubly_linked_list *list)
{
  return list->last->data;
}

void *
util_doubly_linked_list_get (struct util_doubly_linked_list *list, size_t idx)
{
  if (idx > list->size)
    return util_doubly_linked_list_get_last (list);
  else if (idx <= 0)
    return util_doubly_linked_list_get_first (list);
  else
    {
      struct util_node *cur = _util_node_get (list, idx);
      return cur->data;
    }
  return NULL;
}

void
util_doubly_linked_list_foreach (struct util_doubly_linked_list *list,
                                 void (*f) (void *, size_t *))
{
  struct util_node *cur;

  for (cur = list->first; cur; cur = cur->next)
    f (cur->data, &cur->size);
}
