/*
 * LICENSE...
 */
#ifndef UTIL_ARRAY_H
#define UTIL_ARRAY_H

#define __need_size_t
#include <stddef.h>

typedef unsigned char byte;

struct util_array
{
  byte *data;
  size_t _data_size;
  size_t capacity;
  size_t size;
};

struct util_array util_array_new (size_t data_size, size_t capacity);
void util_array_push (struct util_array *array, const void *data);
void *util_array_pop (struct util_array *array);
void util_array_delete (struct util_array *array);

#endif /* UTIL_ARRAY_H */
