#include "ast_exec.h"

int and_or(struct shell_env *env, struct ast *ast)
{
  if (ast->nb_children == 0)
    return 1; // TODO ERROR SCL
  int res = ast_exec(env, ast->children[0]);
  if (ast->nb_children < 2 || (res && strcmp(ast->values[0], "&&")))
    return res;
  return ast_exec(env, ast->children[1]);
}
