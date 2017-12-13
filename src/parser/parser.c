#include <stdlib.h>

#include "parser.h"
#include "parser_1.h"
#include "lexer.h"

struct ast *ast_create(int *return_value)
{
  struct token token;
  struct context context =
  {
    &token, NULL, 0, 0, 1, 0
  };
  struct ast *ast = parse_input(return_value, &context);
  return ast;
}

struct ast *parse_input(int *return_value, struct context *context)
{
  struct ast *input = ast_init();
  *return_value = 0;
  if (!input)
  {
    return_value = 1; //error
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

