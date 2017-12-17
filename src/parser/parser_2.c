#include <stdlib.h>
#include <string.h>

#include "parser.h"

struct ast *parser_shell_command(int *return_value, struct context *context);
struct ast *parse_funcdef(int *return_value, struct context *context);
struct ast *parse_redirection(int *return_value, struct context *context);

struct ast *parse_prefix(int *return_value, struct context *context)
{
  return_value = return_value;
  context = context;
  return NULL;
}


struct ast *parse_element(int *return_value, struct context *context)
{
  struct ast *element = ast_init();
  struct ast *child = ast_init();

  if (!(get_next_token(context) && element && child) ||
      context->token->type == NEW_LINE)
  {
    context->token_used = 0;
    ast_destroy(element);
    ast_destroy(child);
    return NULL;
  }

  return_value = return_value;

  context->token_used = 1;
  element->type = ELEMENT;
  ast_add_child(element, child, NULL);
  child->type = WORD;

  char *token = malloc(sizeof(char) * (strlen(context->token->token + 1)));
  token[strlen(context->token->token)] = 0;
  strcpy(token, context->token->token);

  child->values[0] = token;
  return element;
}
