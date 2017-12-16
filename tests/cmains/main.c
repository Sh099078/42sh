#include <stdio.h>

#include "create_hard_ast.h"
#include "ast_exec.h"
#include "struct.h"

int main(int argc, char **argv)
{
  struct shell_env *env = shell_env_init();
  struct ast *ast = create_and_or_ast(argc, argv);
  ast_exec(env, ast);
  return 0;
}