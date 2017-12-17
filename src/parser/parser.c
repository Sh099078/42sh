#include <stdlib.h>

#include "parser.h"

struct ast *abort_parsing(struct ast *ast, int *return_value)
{
  *return_value = 1; //error
  ast_destroy(ast);
  return NULL;
}

struct ast *ast_create(int *return_value)
{
  struct token token;
  token.token = NULL;
  struct context context =
  {
    &token, NULL, 0, 0, 1, 1, 0
  };
  struct ast *ast = parse_input(return_value, &context);
  if (token.token)
    free(token.token);
  if (context.line)
    free(context.line);
  return ast;
}

struct ast *parse_input(int *return_value, struct context *context)
{
  struct ast *input = ast_init();
  *return_value = 0;
  if (!input)
  {
    *return_value = 1; //error
    return input;
  }
  input->type = INPUT;
  if (!get_next_token(context) || context->token->type == NEW_LINE)
    return input;
  context->token_used = 0;
  struct ast *list = parse_list(return_value, context);
  if (list)
  {
    ast_add_child(input, list, NULL);
    if (!get_next_token(context) || context->token->type == NEW_LINE)
      return input;
  }
  *return_value = 1; //error
  ast_destroy(input);
  return NULL;
}

