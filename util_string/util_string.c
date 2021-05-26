#include "util_string.h"

#include <stdlib.h>
#include <string.h>

struct util_string
util_string_new_dft (void)
{
  return (struct util_string){ NULL, 0, 0 };
}

struct util_string
util_string_new_size (size_t size)
{
  return (struct util_string){ (char *)malloc (size), 0, size };
}

struct util_string
util_string_new (const char *data, size_t len, size_t size)
{
  struct util_string string = { NULL, len, size };

  if (size && len > size)
    string.len = size - 1;
  if (len && !size)
    string.size = len + 1;
  if (!data)
    {
      string.len = 0;
      if (string.size)
        {
          string.data = (char *)malloc (string.size);
          *string.data = '\0';
        }
    }
  else
    {
      if (string.len)
        string.len = strnlen (data, string.len);
      else if (string.size)
        string.len = strnlen (data, string.size - 1);
      else
        {
          string.len = strlen (data);
          string.size = string.len + 1;
        }
      string.data = (char *)malloc (string.size);
      *(char *)(memcpy (string.data, data, string.len) + string.len) = '\0';
    }
  return string;
}

void
util_string_set (struct util_string *string, const char *data, size_t len)
{
  size_t length = len            ? strnlen (data, len)
                  : string->size ? strnlen (data, string->size - 1)
                                 : strlen (data);

  if (string->size && length >= string->size)
    length = string->size - 1;

  if (!string->data)
    {
      string->data = (char *)malloc (length + 1);
      string->size = length + 1;
    }
  strncpy (string->data, data, length);
  string->data[length + 1] = '\0';
  string->len = length;
}
