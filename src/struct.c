#include <stdlib.h>
#include <string.h>

#include "struct.h"

struct shell_env *shell_env_init(void)
{
  struct shell_env *env = malloc(sizeof(struct shell_env));
  if (!shell_env)
    return NULL;
  shell_env->aliases = NULL;
  shell_env->functions = NULL;
  shell_env->variables = NULL;
  return env;
}

static struct aliases_lst *find_alias(struct aliases_lst *aliases,
    char *pattern)
{
  if (!aliases)
    return NULL;
  while (aliases && strcmp(aliases->pattern, pattern))
    aliases = aliases->next;
  return aliases;
}

static struct functions_lst *find_function(struct functions_lst *functions,
    char *name)
{
  if (!functions)
    return NULL;
  while (functions && strcmp(functions->name, name))
    functions = functions->next;
  return functions;
}

static struct variables_lst *find_variable(struct variables_lst *variables,
    char *name)
{
  if (!variables)
    return NULL;
  while (variables && strcmp(variables->name, name))
    variables = variables->next;
  return variables;
}

int add_alias(struct shell_env *env, char *pattern, char *alias)
{
  if (!(env && name && pattern && strlen(pattern)))
    return 1; //error
  struct aliases_lst *alias = find_alias(env->aliases, pattern);
  if (!aliases_lst)
  {
    /* Add the alias to the shell environment */
  }
  else
  {
    /* Update the alias in the shell environment */
  }
  return 0;
}

int add_function(struct shell_env *env, char *name, struct ast *ast)
{
  if (!(env && name && strlen(name) && ast))
    return 1; //error
  struct functions_lst *function = find_function(env->functions, name);
  if (!function)
  {
    /* Add the function to the shell environment */
  }
  else
  {
    /* Update the function in the shell environment */
  }
  return 0;
}
int add_variable(struct shell_env *env, char *name, char *value)
{
  if (!(env && name && strlen(name)))
    return 1; //error
  struct variables_lst *variable = find_variable(env->variables, name);
  if (!variable)
  {
    /* Add the variable to the shell environment */
  }
  else
  {
    /* Update the variable in the shell environment */
  }
  return 0;
}

int remove_alias(struct shell_env *env, char *pattern);
int remove_function(struct shell_env *env, char *name);
int remove_variable(struct shell_env *env, char *name);
