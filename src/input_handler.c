#include <string.h>
#include <stdlib.h>

#include "input_handler.h"

/*
** Returns the concatenation of the strings s1 and s2.
** NB: freeing s1 and s2 must be done outside this function
** if needed. s1 and s2 must be null terminated.
*/
static char *str_concat(const char *s1, const char *s2)
{
  size_t s1_sz = strlen(s1);
  size_t s2_sz = strlen(s2);
  size_t str_sz = s1_sz + s2_sz;
  char *concat = malloc(sizeof(char) * (str_sz + 1));
  if (!concat)
    return NULL;
  strcpy(concat, s1);
  strcpy(concat + s1_sz, s2);
  //concat[str_sz] = 0;
  return concat;
}

char *get_next_line(FILE *input, const char *curr_line)
{
  char *line = NULL;
  size_t line_sz = 0;
  ssize_t nb_read = getline(&line, &line_sz, input);
  if (nb_read == -1)
    return NULL; /* end of input */
  if (!curr_line && nb_read != -1)
    return line; /* first attempt to build an ast */
  return str_concat(curr_line, line); /* new attempt to build the ast */
}

