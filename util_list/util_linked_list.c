#include "util_linked_list.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef struct util_linked_list util_list;

struct util_node
{
  byte *data;
  size_t size;
  struct util_node *next;
};

static struct util_node *
_new_node (const byte *data, size_t size, struct util_node *next,
           struct util_node *prev)
{
  struct util_node *node = (struct util_node *)malloc (sizeof (*node));

  node->data = (byte *)malloc (size);
  memcpy (node->data, data, size);
  node->size = size;
  if (prev)
    prev->next = node;
  if (next)
    node->next = next;
  else
    node->next = NULL;

  return node;
}

util_list
util_linked_list_new (void)
{
  return (util_list){ NULL, NULL, 0 };
}

void
util_linked_list_push (util_list *list, const void *data, size_t size)
{
  list->last = _new_node (data, size, NULL, list->last);
  if (!list->first)
    list->first = list->last;
  list->size++;
}

void
util_linked_list_prepend (util_list *list, const void *data, size_t size)
{
  list->first = _new_node (data, size, list->first, NULL);
  if (!list->last)
    list->last = list->first;
  list->size++;
}

void
util_linked_list_insert (util_list *list, size_t idx, const void *data,
                         size_t size)
{
  if (idx <= 0)
    util_linked_list_prepend (list, data, size);
  else if (idx >= list->size)
    util_linked_list_push (list, data, size);
  else
    {
      struct util_node *cur;
      size_t i;

      i = 0;
      for (cur = list->first; cur; cur = cur->next)
        if (i++ == idx - 1)
          break;

      _new_node (data, size, cur->next, cur);
      list->size++;
    }
}

void *
util_linked_list_pop (util_list *list)
{
  if (list->size)
    {
      struct util_node *last;
      void *item = list->last->data;

      for (last = list->first; last; last = last->next)
        {
          if (last->next == list->last)
            {
              list->last = last;
            }
        }
      free (last);

      if (list->last)
        list->last->next = NULL;

      if (!--list->size)
        list->first = list->last = NULL;

      return item;
    }
  return NULL;
}

void *
util_linked_list_dequeue (util_list *list)
{
  struct util_node *const head = list->first;

  if (head)
    {
      void *element;

      if (head->next)
        list->first = head->next;
      element = head->data;
      free (head);

      if (!--list->size)
        list->first = list->last = NULL;

      return element;
    }
  return NULL;
}

void *
util_linked_list_remove (util_list *list, size_t idx)
{
  if (idx <= 0)
    return util_linked_list_dequeue (list);
  else if (idx >= list->size - 1)
    return util_linked_list_pop (list);
  else /* has at least two elements. */
    {
      struct util_node *cur, *removed;
      void *element;
      size_t i = 0;

      for (cur = list->first; cur; cur = cur->next)
        {
          if (i++ == idx - 1)
            {
              removed = cur->next;
              cur->next = removed->next;
              element = removed->data;
              free (removed);

              if (!--list->size)
                list->first = list->last = NULL;

              return element;
            }
        }
    }
  return NULL;
}

void *
util_linked_list_get_first (struct util_linked_list *list)
{
  return list->first ? list->first->data : NULL;
}

void *
util_linked_list_get_last (struct util_linked_list *list)
{
  return list->last ? list->last->data : NULL;
}

void *
util_linked_list_get (util_list *list, size_t idx)
{
  struct util_node *cur = list->first;
  size_t i;

  for (i = 0; cur && i != idx; ++i)
    cur = cur->next;

  return cur;
}

void
util_linked_list_foreach (struct util_linked_list *list,
                          void (*f) (void *, size_t *))
{
  struct util_node *cur;

  for (cur = list->first; cur; cur = cur->next)
    f (cur->data, &cur->size);
}

void
util_linked_list_delete (util_list *list)
{
  while (list->first)
    free (util_linked_list_remove (list, 2));
}
