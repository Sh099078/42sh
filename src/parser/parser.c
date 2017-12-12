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
  struct ast *ast = parse_list(return_value, context);
  if (!get_next_token(context) || context->token->type == NEW_LINE)
  {
    *return_value = 0; //no error
    return ast;
  }
  *return_value = 1; // Error while parsing
  ast_destroy(ast);
  return NULL;
}

