#include "ast_exec.h"

/**
 * translate a for sequence in a string array
 * Only handle regular "1 2 3 4"-like sequences for now
 * @param  ast sequence AST node
 * @return     string array to iterate on, or NULL on error
 */
static char **get_seq(struct ast *ast)
{
  if (!ast)
    return NULL;
  size_t buf_size = 4096;
  char *str = ast->values[0];
  char **seq = malloc(sizeof(char *) * buf_size);
  char *nextToken = strtok(str, " ");
  size_t i = 0;
  for (; nextToken; i++)
  {
    if (i == buf_size)
    {
      buf_size *= 2;
      char **tmp = realloc(seq, sizeof(char *) * buf_size);
      if (!tmp)
      {
        free(seq);
        return NULL;
      }
      seq = tmp;
    }
    seq[i] = nextToken;
    nextToken = strtok(NULL, " ");
  }
  seq[i + 1] = NULL;
  return seq;
}

int rule_for(struct shell_env *env, struct ast *ast)
{
  // TODO error checking
  char **seq = get_seq(ast->children[0]); // TODO
  char *key = ast->children[1]->values[0];
  int status = 0;
  for (size_t i = 0; seq[i]; i++)
  {
    add_variable(env, key, seq[i]); // updates variable
    status = ast_exec(env, ast->children[2]);
  }
  return status;
}
