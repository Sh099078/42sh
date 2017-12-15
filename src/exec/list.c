#include "ast_exec.h"


/* Sequential and Asynchronous list */
int list(struct shell_env *env, struct ast *ast)
{
  if (!ast)
    return 1; // error
  int status = 0;
  for (size_t i = 0; i < ast->nb_children; i++)
  {
    if (ast->values[i][0] == '&')
    {
      pid_t pid = fork();
      if (pid == 0)
        ast_exec(env, ast->children[i]); // asynchronous list
      else if (pid < 0)
      {
        warn("execution failed: could not execute asynchronous list");
        return 1; // TODO check SCL exit code
      }
      status = 0; // exit status of asynchronous list is 0
    }
    status = ast_exec(env, ast->children[0]); // sequential list
  }
  return status;
}
