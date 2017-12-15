#include "ast_exec.h"

int input(struct shell_env *env, struct ast *ast)
{
  if (!ast || !ast->nb_children)
    return 0;
  return ast_exec(env, ast->children[0]);
}
