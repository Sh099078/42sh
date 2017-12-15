#include "ast_exec.h"

int pipeline(struct shell_env *env, struct ast *ast)
{
  // check nb_children and null ast
  // TODO check extras for bang
  int status = 0;
  for (size_t i = 0; i < ast->nb_children; i++)
  {
    status = ast_exec(env, ast->children[i]);
    // TODO handle redirection dup2 pipe exec fork etc.
  }
  return status;
}
