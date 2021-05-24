/*
 * LICENSE...
 */

#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string.h>

struct util_string
{
  char *data;
  size_t len;
  size_t size;
};

struct util_string util_string_new_dft (void);
struct util_string util_string_new_size (size_t size);
struct util_string util_string_new (const char *data, size_t len, size_t size);

void util_string_set (struct util_string *string, const char *data,
                      size_t len);

#endif /* UTIL_STRING_H */
