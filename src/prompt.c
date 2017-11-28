#include <stdio.h>
#include <stdlib.h>

#include "input_handler.h"

int prompt(FILE *input)
{
  char *line = NULL;
  while (1)
  {
    char *new_line = get_next_line(input, line);
    if (!new_line)
      break;
    char *tmp = line;
    line = new_line;
    free(tmp);
    printf("%s\n", line);
  }
  return 1;
}

int main(int argc, char **argv)
{
  if (argc != 2)
    return 1;
  FILE *input = fopen(argv[1], "r");
  if (!input)
    return 1;
  if (prompt(input))
    return 0;
  return 1;
}
