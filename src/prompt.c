#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "ast_exec.h"
#include "struct.h"
#include "struct.h"
#include "ast_printer.h"
#include "options.h"

int prompt(struct options options)
{
  struct ast *ast;
  struct shell_env *env = shell_env_init();
  if (!env)
    return 1;

  int return_value = 0;
  while (1)
  {
    ast = NULL;
    ast = ast_create(&return_value);
    if (!ast)
      continue;
    ast_exec(env, ast);
    if (options.shopt_vars & 1)
      ast_to_dot(ast);
    ast_destroy(ast);
  }
  free(env);
  ast_destroy(ast);
  return return_value;
}

int main(int argc, char **argv)
{
  FILE *input = fdopen(0, "r");
  if (!input)
    return 2;
  struct options options = options_get(argc, argv);
  return prompt(options);
}
