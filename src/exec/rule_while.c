#include "ast_exec.h"

/**
 * The compound-list-1 will be executed, and if it has a non-zero exit status,
 * the while command will complete. Otherwise, the compound-list-2 will be
 * executed, and the process will repeat.
 * @param  ast node to evaluate in parsing AST
 * @return  The exit status of the while loop will be the exit status of the
 * last compound-list-2 executed, or zero if none was executed.
 */
int rule_while(struct ast *ast)
{
  int cmpdlist2 = 0;
  while (ast_exec(ast->children[0]) == 0)
    cmpdlist2 = ast_exec(ast->children[1]);
  return cmpdlist2;
}
