#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "lexer.h"

static void context_free_line(struct context *context)
{
  if (!context->line)
    return;
  free(context->line);
  context->line = NULL;
  context->line_index = 0;
}

static int ask_new_line(struct context *context)
{
  context_free_line(context);
  char *output = isatty(0) ? (context->first_line ? "42sh$ " : "> ") : "\n";
  context->line = readline(output);
  if (!context->line)
    return 0; //no more input --> exit 42sh
  while (context->line[context->line_index] == ' ')
    context->line_index++;
  context->first_line = 0;
  return 1;
}

static void token_init(struct context *context)
{
  struct token *token = context->token;
  if (token->token)
    free(token->token);
  token->token = NULL;
  token->type = TOKEN; //default value
  context->token_size = 0;
}

static int add_char_to_token(char c, struct context *context)
{
  struct token *token = context->token;
  if (!token->token)
  {
    token->token = malloc(sizeof(char) * 2);
    context->token_size++;
  }
  else
    token->token = realloc(token->token, (++context->token_size + 1));
  if (!token->token)
    return 0; //malloc failed.
  token->token[context->token_size - 1] = c;
  token->token[context->token_size] = 0;
  return 1;
}

/*
static void test_new_line(struct context *context)
{
  if (!context->token->token)
  {
    token_init(context);
    context->token->type = NEW_LINE;
  }
}
*/

int get_next_token(struct context *context)
{
  struct token *token = context->token;
  int simple_quote = 0;
  int double_quote = 0;
  if ((!context->line || !context->line[context->line_index]) && !ask_new_line(context))
      return 0;
  token_init(context);

  while (1)
  {
    int quoting = 0;
    char c = context->line[context->line_index];
    context->line_index = c ? context->line_index + 1 : context->line_index;
    if (c == '\\' && !simple_quote)
    {
      quoting = 1;
      c = context->line[context->line_index];
      if (c)
        context->line_index++;
    }
    if (!c && !quoting)
    {
      context->first_line = 1;
      break;
    }
    if (!c && quoting)
    {
      if (!ask_new_line(context))
        break;
      else
        c = context->line[context->line_index++];
    }
    if (c == ' ' && !(simple_quote || double_quote))
      break;
    if (!add_char_to_token(c, context))
      return 1; //malloc failed
    if (c == '"' && !simple_quote && !quoting)
    {
      double_quote = !double_quote;
      if (!double_quote && context->line[context->line_index] == ' ')
        break;
    }
    if (c == '\'' && !double_quote)
    {
      simple_quote = !simple_quote;
      if (!simple_quote && context->line[context->line_index] == ' ')
        break;
    }
  }
  if (context->line[context->line_index] == ' ')
    context->line_index++;
  return token->token || token->type == NEW_LINE;
}

/*#include <stdio.h>
int main(void)
{
  struct token token;
  token.token = NULL;
  struct context context = { &token, NULL, 0, 0, 1 };
  for(int i = 0; i < 100; i++)
  {
    if (!get_next_token(&context))
      return 0;
    printf("%s\n", token.token);
  }
  return 0;
}*/
