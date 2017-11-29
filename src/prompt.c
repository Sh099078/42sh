#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "input_handler.h"

int prompt(FILE *input)
{
  char *line = NULL;
  while (1)
  {
    if (isatty(0))
      printf("42sh ");
    char *new_line = get_next_line(input, line);
    if (!(new_line && new_line[0]))
      break;
    char *tmp = line;
    line = new_line;
    free(tmp);
    printf("%s\n", line);
  }
  return 0;
}

int main(void)
{
  FILE *input = fdopen(0, "r");
  if (!input)
    return 2;
  if (prompt(input))
    return 0;
  return 1;
}
