#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "ast_exec.h"
#include "struct.h"
#include "struct.h"

/*
static void error_handler(int return_value, char **line)
{
  switch (return_value)
  {
    case 1:
      // lexor error ; ask for more lines and try again
      break;
    case 2:
      // parser error : syntax error, incorrect var...
      free(*line);
      *line = NULL;
      break;
    default:
      break;
  }
}
*/

int prompt(void)
{
  struct shell_env *env = shell_env_init();
  if (!env)
    return 1;

  int return_value = 0;
  while (1)
  {
    struct ast *ast = ast_create(&return_value);
    if (!ast)
      break;
    ast_exec(env, ast);
    ast_destroy(ast);
  }

  free(env);
  return return_value;
}

int main(void)
{
  FILE *input = fdopen(0, "r");
  if (!input)
    return 2;
  return prompt();
}
