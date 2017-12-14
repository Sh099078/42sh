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
  struct ast *and_or = ast_init();
  struct ast *pipeline = parse_pipeline(return_value, context);
  if (!and_or)
  {
    *return_value = 1; //error
    ast_destroy(pipeline);
    return NULL;
  }
  for (; pipeline; pipeline = parse_pipeline(return_value, context))
  {
    get_next_token(context);
    if (!(context->token->type == AND_IF || context->token->type == OR_IF))
    {
      context->token_used = 0;
      break;
    }
    else
      ast_add_child(and_or, pipeline, context->token->token);
    while (context->token->type == NEW_LINE)
    {
      context->token_used = 1;
      get_next_token(context);
    }

  }
  if (and_or->nb_children == 0)
  {
    ast_destroy(and_or);
    *return_value = 1; //error
    return NULL;
  }
  return and_or;
}

struct ast *parse_pipeline(int *return_value, struct context *context)
{
  struct ast *pipeline = ast_init();
  if (!(get_next_token(context) && pipeline))
  {
    *return_value = 1; //error
    ast_destroy(pipeline);
    return NULL;
  }
  context->token_used = context->token->type == Bang ? 1 : 0;
  struct ast *command = parse_command(return_value, context);
  for (; command; command = parse_command(return_value, context))
  {
    get_next_token(context);
    char *token = context->token->token;
    if (strcmp(token, "|"))
    {
      context->token_used = 0;
      break;
    }
    while (get_next_token(context) && context->token->type == NEW_LINE)
      context->token_used = 1;
  }
}
struct ast *parse_command(int *return_value, struct context *context);
struct ast *parse_simple_command(int *return_value, struct context *context);
