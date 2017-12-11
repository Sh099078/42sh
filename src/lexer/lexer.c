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

static void token_update_type(struct token *token)
{
  if (!token->token)
  {
    token->type = NEW_LINE;
    return;
  }
  char *reserved_words[] =
  {
    "if", "then", "else", "elif", "fi", "do", "done", "case", "esac", "while",
    "until", "for", "{", "}", "!", "in", "&&", "||", ";;", "<<", ">>", "<&",
    ">&", "<>", "<<-", ">|", NULL
  };
  enum token_type reserved_words_type[] =
  {
    If, Then, Else, Elif, Fi, Do, Done, Case, Esac, While, Until, For, Lbrace,
    Rbrace, Bang, In, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND, GREATAND,
    LESSGREAT, DLESSDASH, CLOBBER
  };
  for (unsigned i = 0; reserved_words[i]; i++)
  {
    if (strcmp(token->token, reserved_words[i]) == 0)
    {
      token->type = reserved_words_type[i];
      return;
    }
  }
  if (token->token[0] >= '0' && token->token[0] <= '9')
  {
    for (unsigned j = 1; token->token[j] && ((token->token[j] <= '9' &&
        token->token[j] >= '0') || (token->token[j] == '<' ||
          token->token[j] == '>')); j++)
      if (token->token[j] == '<' || token->token[j] == '>')
        token->type = IO_NUMBER;
    return;
  }
  token->type = TOKEN;
}

int get_next_token(struct context *context)
{
  int simple_quote = 0;
  int double_quote = 0;
  int quoting = 0;
  token_init(context);
  if ((!context->line || !context->line[context->line_index]) && !ask_new_line(context))
      return 0;

  while (1)
  {
    char c = context->line[context->line_index];
    context->line_index = c ? context->line_index + 1 : context->line_index;
    if (c == '\\' && !simple_quote && !quoting)
    {
      quoting = 1;
      c = context->line[context->line_index];
      if (c)
        context->line_index++;
    }
    if (!c)
    {
      if (!(quoting || simple_quote || double_quote))
      {
        context->first_line = 1;
        break;
      }
      quoting = 0;
      if (!ask_new_line(context))
        break;
      quoting = 0;
      continue;
      c = context->line[context->line_index++];
    }
    if (c == ' ' && !(simple_quote || double_quote))
      break;
    if (!add_char_to_token(c, context))
      return 1; //malloc failed
    quoting = c != '"' && c != '\'' ? 0 : quoting;
    if (c == '"' && !simple_quote && !quoting)
    {
      double_quote = !double_quote;
      if (!double_quote && (context->line[context->line_index] == ' ' ||
          context->line[context->line_index] == '\0'))
        break;
      if (context->line[context->line_index] == '\0')
        double_quote = 1;
    }
    else if (c == '\'' && !double_quote && !quoting)
    {
      simple_quote = !simple_quote;
      if (!simple_quote && (context->line[context->line_index] == ' ' ||
            context->line[context->line_index] == '\0'))
      {
        //if (simple_quote && !add_char_to_token('\n', context))
          //return 1;
        break;
      }
      if (context->line[context->line_index] == '\0')
        simple_quote = 1;
    }
    else if (quoting)
      quoting = 0;
  }
  if (context->line[context->line_index] == ' ')
    context->line_index++;
  token_update_type(context->token);
  return 1;
  //return token->token || token->type == NEW_LINE;
}

#include <stdio.h>
static void print_token_type(struct token token)
{
  if (token.type == TOKEN)
    printf("TOKEN");
  else if (token.type == NEW_LINE)
    printf("NEW_LINE");
  else if (token.type == IO_NUMBER)
    printf("IO_NUMBER");
  else
  {
    char *reserved_words[] =
    {
      "If", "Then", "Else", "Elif", "Fi", "Do", "Done", "Case", "Esac", "While",
      "Until", "For", "Lbrace", "Rbrace", "Bang", "In", "AND_IF", "OR_IF",
      "DSEMI", "DLESS", "DGREAT", "LESSAND",
      "GREATAND", "LESSGREAT", "DLESSDASH", "CLOBBER", NULL
    };
    enum token_type reserved_words_type[] =
    {
      If, Then, Else, Elif, Fi, Do, Done, Case, Esac, While, Until, For, Lbrace,
      Rbrace, Bang, In, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND, GREATAND,
      LESSGREAT, DLESSDASH, CLOBBER
    };
    unsigned i;
    for (i = 0; reserved_words_type[i] != token.type; i++)
      continue;
    printf("%s", reserved_words[i]);
  }
}
int main(void)
{
  struct token token;
  token.token = NULL;
  struct context context = { &token, NULL, 0, 0, 1 };
  for(int i = 0; i < 100; i++)
  {
    if (!get_next_token(&context))
      return 0;
    printf("%s ", token.token);
    print_token_type(token);
    printf("\n");
  }
  return 0;
}
