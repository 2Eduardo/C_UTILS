#include <stdio.h>

#include "util_string.h"

/* new (NULL, 0, 0) -> string [0,0,0]
 * new (NULL, 0, 1) -> string [\0, 0, size]
 * new (NULL, 1, 0) -> string [\0, 0, len+1]
 * new (NULL, 1, 1) -> string [\0, 0, size]
 * new (data, 0, 0) -> string [dta, dtalen, dtalen+1]
 * new (data, 0, 1) -> string [dta, dtalen || size-1, size]
 * new (data, 1, 0) -> string [dta, len, len+1]
 * new (data, 1, 1) -> string [dta, dtalen, size]
 */

void
check (struct util_string *string)
{
  if (!string->data)
    puts ("(null)");
  else if (!*string->data)
    puts ("\\0");
  else
    puts (string->data);
  printf ("%lu\n", string->len);
  printf ("%lu\n", string->size);
  printf ("--------\n");
}
int
main ()
{
  struct util_string string[]
      = { util_string_new (NULL, 0, 0),     util_string_new (NULL, 0, 10),
          util_string_new (NULL, 10, 0),    util_string_new (NULL, 10, 10),
          util_string_new (NULL, 11, 10),   util_string_new (NULL, 10, 11),
          util_string_new ("Hello", 0, 0),  util_string_new ("Hello", 0, 10),
          util_string_new ("Hello", 10, 0), util_string_new ("Hello", 10, 10),
          util_string_new ("Hello", 4, 10), util_string_new ("Hello", 10, 4) };

  for (int i = 0; i < sizeof (string) / sizeof (*string); ++i)
    {
      check (&string[i]);
      if (string[i].data)
        free (string[i].data);
    }

  return 0;
}