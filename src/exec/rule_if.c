#include "exec_ast.h"

int exec_rule_if(struct ast *ast)
{
  if (ast->nb_children < 2)
    return 1; // TODO error
  int res = ast_exec(ast->children[0]);
  if (!res)
    return ast_exec(ast->children[1]);
  else if (ast->nb_children > 2)
    return ast_exec(ast->children[2]);
  return 0; // SCL says to return 0 if no else clause.
}
