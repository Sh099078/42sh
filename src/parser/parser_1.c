#include <stdlib.h>

#include "parser_1.h"
#include "lexer.h"
#include "string.h"

struct ast *parse_list(int *return_value, struct context *context)
{
  struct ast *first_and_or = parse_and_or(return_value, context);
  struct ast *list = ast_init();

  if (!(list || first_and_or))
  {
    *return_value = 1; //error
    ast_destroy(first_and_or);
    ast_destroy(list);
    return NULL;
  }

  if (!get_next_token(context) || (strcmp(context->token->token, ";")
        && strcmp(context->token->token, "&")))
      return NULL; //error
  first_and_or->value = context->token->token;

  for (struct ast *next_and_or = parse_and_or(return_value, context);
       next_and_or; next_and_or = parse_and_or(return_value, context))
  {
    if (!get_next_token(context))
      return NULL; //error
    if (strcmp(context->token->token, ";") && strcmp(context->token->token, "&"))
      return NULL; //error
    next_and_or->value = context->token->token;
    if (!ast_add_child(list, next_and_or))
    {
      *return_value = 1;
      ast_destroy(list);
      return NULL;
    }
  }
  return list;
}
struct ast *parse_and_or(int *return_value, struct context *context);
struct ast *parse_pipeline(int *return_value, struct context *context);
struct ast *parse_command(int *return_value, struct context *context);
struct ast *parse_simple_command(int *return_value, struct context *context);
