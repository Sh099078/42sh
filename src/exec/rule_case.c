#include "ast_exec.h"

int case_clause(struct ast *ast, char *var)
{
  int i = 0;
  int ok = 0;
  while(children[i]->type == 21 && ok == 0)
  {
    if(strcmp(children[i]->value, var) == 0)
      ok++;
    i++;
  }
  if(ok == 0)
    return -1;
  else
    return ast_exec(ast->children[i]);
}
