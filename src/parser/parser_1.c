#include <stdlib.h>

#include "parser_1.h"
#include "lexer.h"
#include "string.h"

struct ast *parse_list(int *return_value, struct context *context)
{
  return_value = return_value;
  context = context;
  return NULL;
}
struct ast *parse_and_or(int *return_value, struct context *context)
{
  return_value = return_value;
  context = context;
  return NULL;
}

struct ast *parse_pipeline(int *return_value, struct context *context);
struct ast *parse_command(int *return_value, struct context *context);
struct ast *parse_simple_command(int *return_value, struct context *context);
