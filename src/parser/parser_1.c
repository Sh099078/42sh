#include <stdlib.h>

#include "parser_1.h"
#include "lexer.h"
#include "string.h"

struct ast *parse_list(int *return_value, struct context *context)
{
  struct ast *list = ast_init();
  struct ast *and_or = parse_and_or(return_value, context);
  if (!list)
  {
    *return_value = 1; //error
    ast_destroy(and_or);
    return NULL;
  }
  for (; and_or; and_or = parse_and_or(return_value, context))
  {
    get_next_token(context);
    if (and_or)
      ast_add_child(list, and_or, context->token->token);
    char *token = context->token->token;
    if (strcmp(token, ";") && strcmp(token, "&"))
    {
      context->token_used = 0;
      break;
    }
  }
  if (!list->nb_children)
  {
    *return_value = 1; //error
    ast_destroy(list);
    return NULL;
  }
  return list;
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
