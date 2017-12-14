#include "ast_exec.h"

int exec_and_or(struct shell_env *env, struct ast *ast)
{
  if (ast->nb_children < 2)
    return 1; // TODO ERROR SCL
  int res = ast_exec(env, ast->children[0]);
  if (res && strcmp(ast->values[0], "&&"))
    return res;
  return ast_exec(env, ast->children[1]);
}
