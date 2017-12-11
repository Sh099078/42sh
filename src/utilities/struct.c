#include <stdlib.h>
#include <string.h>

#include "struct.h"

struct shell_env *shell_env_init(void)
{
  struct shell_env *shell_env = malloc(sizeof(struct shell_env));
  if (!shell_env)
    return NULL;
  shell_env->aliases = NULL;
  shell_env->functions = NULL;
  shell_env->variables = NULL;
  return shell_env;
}

// TODO
static struct aliases_lst *find_alias(struct aliases_lst *aliases,
    char *pattern)
{
  if (!aliases)
    return NULL;
  while (aliases && strcmp(aliases->pattern, pattern))
    aliases = aliases->next;
  return aliases;
}

// TODO
static struct functions_lst *find_function(struct functions_lst *functions,
    char *name)
{
  if (!functions)
    return NULL;
  while (functions && strcmp(functions->name, name))
    functions = functions->next;
  return functions;
}
/**
 * Variables are stored as "key=value" strings, returns null terminated key
 * string
 *
 * @param  keyvalue "key=value" string
 * @return          null terminated key string representation, or NULL on error
 */
static char *variable_get_key(char *keyvalue)
{
  char *s = malloc(strlen(keyvalue));
  if (!s)
    return NULL;
  strcpy(s, keyvalue);
  strtok(s, "=");
  if (!s)
  {
    free(s);
    return NULL;
  }
  return s;
}

/**
 * Find variable index in variable list of shell environment
 * @param  variables variables list
 * @param  name      key of variable we are looking for
 * @return           index of the desired variable, or -1 if not found
 */
static int *find_variable(struct variables_lst *variables,
    char *name)
{
  if (!variables)
    return -1;
  for (size_t i = 0; i < variables->size; i++)
  {
    if (strcmp(variable_get_key(variables->list[i]), name) == 0)
      return i;
  }
  return -1;
}

// TODO
int add_alias(struct shell_env *env, char *pattern, char *alias)
{
  if (!(env && alias && pattern && strlen(pattern)))
    return 1; //error
  struct aliases_lst *aliases_lst = find_alias(env->aliases, pattern);
  if (!aliases_lst)
  {
    // Add the alias to the shell environment
  }
  else
  {
    // Update the alias in the shell environment
  }
  return 0;
}

// TODO
int add_function(struct shell_env *env, char *name, struct ast *ast)
{
  if (!(env && name && strlen(name) && ast))
    return 1; //error
  struct functions_lst *function = find_function(env->functions, name);
  if (!function)
  {
    // Add the function to the shell environment
  }
  else
  {
    // Update the function in the shell environment
  }
  return 0;
}

/**
 * add variable to the variable list of shell environment
 * @param  env   shell environment
 * @param  name  key of the variable
 * @param  value value of the variable
 * @return       index of the inserted variable, or -1 on error
 */
int add_variable(struct shell_env *env, char *name, char *value)
{
  if (!(env && name && strlen(name)))
    return 1; //error
  struct variables_lst *variable = find_variable(env->variables, name);
  if (!variable)
  {
    // Add the variable to the shell environment
  }
  else
  {
    // Update the variable in the shell environment
  }
  return 0;
}

// TODO
int remove_alias(struct shell_env *env, char *pattern);
// TODO
int remove_function(struct shell_env *env, char *name);
int remove_variable(struct shell_env *env, char *name);
