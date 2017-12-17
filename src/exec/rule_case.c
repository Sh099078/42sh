#include "ast_exec.h"

/**
** Checks if a node's children match the case or not
** Goes through the whole children list of the ast and compares their values
** with the given case.
** @param  the environment env, the tree ast we want to check and the var which
** represents the name of the case.
** @return  -1 no case matches, else returns the ast_exec of the che matching
** node
*/
int case_clause(struct shell_env *env, struct ast *ast, char *var)
{
  int i = 0;
  int ok = 0;
  while(ast->children[i]->type == 21 && ok == 0)
  {
    if(strcmp(ast->children[i]->values[0], var) == 0)
      ok++;
    i++;
  }
  if(ok == 0)
    return -1;
  else
    return ast_exec(env, ast->children[i]);
}

int rule_case(struct shell_env *env, struct ast *ast)
{
  char *var = ast->children[0]->values[0];
  for(int i = 1 ; ast->children[i] ; i++)
  {
    if(case_clause(env, ast->children[i], var) != -1)
      return 1;
  }
  return 0;
}
