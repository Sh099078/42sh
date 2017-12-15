#include "ast_exec.h"

int rule_while(struct shell_env *env, struct ast *ast)
{
  int cmpdlist2 = 0;
  while (ast_exec(env, ast->children[0]) == 0)
    cmpdlist2 = ast_exec(env, ast->children[1]);
  return cmpdlist2;
}
