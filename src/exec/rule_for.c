#include "ast_exec.h"

/**
 * translate a for sequence in a string array
 * Only handle regular "1 2 3 4"-like sequences for now
 * @param  ast sequence AST node
 * @return     string array to iterate on, or NULL on error
static char **get_seq(struct ast *ast)
{
  ast = ast;
  return NULL;
}

 * Executes a bash style for loop
 * First child is sequence to iterate on, the second is the variable key, and
 * the third child is the compound_list to execute
 * @param  ast AST node corresponding to the for loop
 * @return     last command executed exit status on success,
 * an error code otherwise
int rule_for(struct shell_env *env, struct ast *ast)
{
  // TODO error checking
  char **seq = get_seq(ast->children[0]); // TODO
  char *key = ast->children[1]->value;
  int status = 0;
  for (size_t i = 0; seq[i]; i++)
  {
    add_variable(env, key, seq[i]); // updates variable
    status = ast_exec(ast->children[2]);
  }
  return status;
}
 */
