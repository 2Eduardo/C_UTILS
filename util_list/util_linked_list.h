/*
 * A linked list is fast to insert in your start and to dequeue, and takes up
 * less memory.
 *
 * LICENSE...
 */
#ifndef UTIL_LINKED_LIST_H
#define UTIL_LINKED_LIST_H

#define __need_size_t
#include <stddef.h>

struct util_node;

struct util_linked_list
{
  struct util_node *first;
  struct util_node *last;
  size_t size;
};

struct util_linked_list util_linked_list_new (void);

void util_linked_list_push (struct util_linked_list *list, const void *data,
                            size_t size);
void util_linked_list_prepend (struct util_linked_list *list, const void *data,
                               size_t size);
void util_linked_list_insert (struct util_linked_list *list, size_t idx,
                              const void *data, size_t size);

/*
 * Remove functions:
 */

void *util_linked_list_pop (struct util_linked_list *list);
void *util_linked_list_dequeue (struct util_linked_list *list);
void *util_linked_list_remove (struct util_linked_list *list, size_t idx);

void *util_linked_list_get_first (struct util_linked_list *list);
void *util_linked_list_get_last (struct util_linked_list *list);
void *util_linked_list_get (struct util_linked_list *list, size_t idx);

void util_linked_list_foreach (struct util_linked_list *list,
                               void (*f) (void *, size_t *));

/* Destroy the list. */
void util_linked_list_delete (struct util_linked_list *list);

#endif /* UTIL_LINKED_LIST_H */
