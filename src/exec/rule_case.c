#include "../../includes/ast_exec.h"

int case_clause(struct ast *ast, char *var)
{
  int i = 0;
  int ok = 0;
  while(ast->children[i]->type == 21 && ok == 0)
  {
    if(strcmp(ast->children[i]->value, var) == 0)
      ok++;
    i++;
  }
  if(ok == 0)
    return -1;
  else
    return ast_exec(ast->children[i]);
}

int rule_case(struct ast *ast)
{
  char *var = ast->children[0]->value;
  for(int i = 1 ; ast->children[i] ; i++)
  {
    if(case_clause(ast->children[i], var) != -1)
      return 1;
  }
  return 0;
}
