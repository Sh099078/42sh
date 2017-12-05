#include <stdlib.h>

#include "parser.h"

struct ast *parse_input(int *return_value, struct context *context);

struct ast *parse_cmd(int *return_value)
{
  *return_value = 0;
  return NULL;
}

