#include <stdlib.h>

#include "parser_1.h"
#include "parser_2.h"
#include "parser.h"
#include "string.h"

struct ast *parse_list(int *return_value, struct context *context)
{
  struct ast *list = ast_init();
  struct ast *and_or = parse_and_or(return_value, context);

  if (!list)
    return abort_parsing(and_or, return_value);

  for (; and_or; and_or = parse_and_or(return_value, context))
  {
    get_next_token(context);
    char *token = context->token->token;
    if (!(strcmp(token, ";") && strcmp(token, "&")))
      ast_add_child(list, and_or, token);
    else
    {
      ast_add_child(list, and_or, NULL);
      context->token_used = 0;
      break;
    }
  }
  //context->token_used = 1;

  if (list->nb_children == 0)
    return abort_parsing(list, return_value);

  return list;
}

struct ast *parse_and_or(int *return_value, struct context *context)
{
  struct ast *and_or = ast_init();
  struct ast *pipeline = parse_pipeline(return_value, context);

  if (!and_or)
    return abort_parsing(pipeline, return_value);

  for (; pipeline; pipeline = parse_pipeline(return_value, context))
  {
    get_next_token(context);
    if (context->token->type == AND_IF || context->token->type == OR_IF)
      ast_add_child(and_or, pipeline, context->token->token);
    else
    {
      ast_add_child(and_or, pipeline, NULL);
      context->token_used = 0;
      break;
    }
    context->token_used = 1;
    while (get_next_token(context) && context->token->type == NEW_LINE)
      context->token_used = 1;
    context->token_used = 0;
  }

  if (and_or->nb_children == 0)
    return abort_parsing(and_or, return_value);

  return and_or;
}

struct ast *parse_pipeline(int *return_value, struct context *context)
{
  struct ast *pipeline = ast_init();

  if (!(get_next_token(context) && pipeline))
    return abort_parsing(pipeline, return_value);

  context->token_used = context->token->type == Bang ? 1 : context->token_used;

  struct ast *command = parse_command(return_value, context);

  for (; command; command = parse_command(return_value, context))
  {
    get_next_token(context);
    if (strcmp(context->token->token, "|") == 0)
      ast_add_child(pipeline, command, context->token->token);
    else
    {
      ast_add_child(pipeline, command, NULL);
      context->token_used = 0;
      break;
    }
    context->token_used = 1;
    while (get_next_token(context) && context->token->type == NEW_LINE)
      context->token_used = 1;
    context->token_used = 0;
  }

  if (pipeline->nb_children == 0)
    abort_parsing(pipeline, return_value);

  return pipeline;
}

struct ast *parse_command(int *return_value, struct context *context)
{
  return parse_simple_command(return_value, context);
}

struct ast *parse_simple_command(int *return_value, struct context *context)
{
  struct ast *simple_command = ast_init();
  struct ast *element = parse_element(return_value, context);

  if (!simple_command)
    abort_parsing(element, return_value);

  simple_command->type = SIMPLE_COMMAND;

  for (; element; element = parse_element(return_value, context))
  {
    ast_add_child(simple_command, element, NULL);
  }

  if (simple_command->nb_children == 0)
    abort_parsing(simple_command, return_value);

  return simple_command;
}
