#include "ast_exec.h"

int rule_if(struct shell_env *env, struct ast *ast)
{
  if (ast->nb_children < 2)
    return 1; // TODO error
  int res = ast_exec(env, ast->children[0]);
  if (!res)
    return ast_exec(env, ast->children[1]);
  else if (ast->nb_children > 2)
    return ast_exec(env, ast->children[2]);
  return 0; // SCL says to return 0 if no else clause.
}
