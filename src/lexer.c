#include <stdlib.h>
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
  context->line = readline(NULL);
  if (!context->line)
    return 0; //no more input --> exit 42sh
  return 1;
}

int get_next_token(struct context *context, struct token *token);
{
  if (!(context->line || ask_new_line(context)))
    return 1; //error: no more input --> exit 42sh

  if (context->line[context->line_index] == '\n')
  {
    context_free_line(context);
    return 0;
  }
  else if (context->line[context->line_index] == '\\' &&
           context->line[context->line_index + 1] == '\n')
  {
    ask_new_line(context);
    return get_next_token(context, token);
    /* continue building same token if its first char isnt an IFS */
  }
  /* Treat operators */
  /* Treat IO_NUMBER */
  /* return TOKEN */
  return 0;
}
