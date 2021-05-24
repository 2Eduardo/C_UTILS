/*
 * LICENSE...
 */

#include "util_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct util_array
util_array_new (size_t data_size, size_t capacity)
{
  // array->_data_size = data_size;
  return (struct util_array){ (byte *)malloc (data_size * capacity), data_size, capacity,
                              0 };
}

void
util_array_push (struct util_array *array, const void *data)
{
  if (array->size < array->capacity)
    {
      size_t offset = array->size * array->_data_size;
      memcpy (array->data + offset, data, array->_data_size);
      array->size++;
    }
}

void *
util_array_pop (struct util_array *array)
{
  size_t offset = array->size * array->_data_size;
  void *result = array->data + offset;

  array->size--;

  return result;
}

void
util_array_delete (struct util_array *array)
{
  free (array->data);
  array->size = array->capacity = 0;
  array->data = NULL;
}

void
print_array (struct util_array *array)
{
  size_t i;
  int *arr = (int *)array->data;

  for (i = 0; i < array->size; ++i)
    printf ("%d ", arr[i]);
  printf ("\n");
}

int
main ()
{
  struct util_array array = util_array_new (sizeof (int), 10);
  const int data[] = { 1, 3, 5 };
  int *p;

  util_array_push (&array, &data[0]);
  util_array_push (&array, &data[1]);
  util_array_push (&array, &data[2]);

  print_array (&array);

  util_array_delete (&array);

  return 0;
}
