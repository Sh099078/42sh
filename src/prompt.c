#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "input_handler.h"
#include "parser.h"
#include "ast_exec.h"
#include "input_handler.h"

static void error_handler(int return_value, char **line)
{
  switch (return_value)
  {
    case 1:
      /* lexor error ; ask for more lines and try again */
      break;
    case 2:
      /* parser error : syntax error, incorrect var... */
      free(*line);
      *line = NULL;
      break;
    default:
      break;
  }
}

int prompt(FILE *input)
{
  char *line = NULL;
  int return_value = 0; //think about the 'echo $?' command.
  while (1)
  {
    if (isatty(0))
      printf("42sh ");

    char *new_line = get_next_line(input, line);
    if (!new_line) /* end of input */
      break;

    if (line)
      free(line);
    line = new_line;

    struct ast *ast = parse_cmd(/*input, */line, &return_value);
    if (!ast)
      error_handler(return_value, &line);
    else
    {
      free(line);
      line = NULL;
      return_value = ast_exec(ast/*, return_value*/);
    }
  }
  return 0;
}

int main(void)
{
  FILE *input = fdopen(0, "r");
  if (!input)
    return 2;
  if (prompt(input))
    return 0;
  return 1;
}
