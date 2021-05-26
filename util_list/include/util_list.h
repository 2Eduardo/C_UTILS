#ifndef UTIL_LIST_H
#define UTIL_LIST_H

#include <util_linked_list.h>
#include <util_doubly_linked_list.h>

#define LIST_OP(OPERATION) util_linked_list_##OPERATION

#define DLIST_OP(OPERATION) util_doubly_linked_list_##OPERATION

typedef struct util_linked_list util_linked_list;
typedef struct util_doubly_linked_list util_doubly_linked_list;

#endif /* UTIL_LIST_H */
