#include <stdlib.h>
#include <string.h>

#include "struct.h"
static struct variables_list *variables_init(void)
{
  struct variables_list *vars = malloc(sizeof(struct variables_list));
  if (!vars)
    return NULL;
  vars->capacity = 10;
  vars->size = 0;
  vars->list = malloc(sizeof(char *) * vars->capacity);
  if (!vars->list)
  {
    free(vars);
    return NULL;
  }
  return vars;
}

static void variables_destroy(struct variables_list *vars)
{
  if (!vars)
    return;
  free(vars->list);
  free(vars);
}

struct shell_env *shell_env_init(void)
{
  struct shell_env *shell_env = malloc(sizeof(struct shell_env));
  if (!shell_env)
    return NULL;
  shell_env->aliases = NULL;
  shell_env->functions = NULL;
  shell_env->variables = variables_init();
  if (!shell_env->variables)
  {
    free(shell_env);
    return NULL;
  }
  return shell_env;
}

void shell_env_destroy(struct shell_env *env)
{
  if (!env)
    return;
  variables_destroy(env->variables);
  free(env);
}
// TODO
static struct aliases_list *find_alias(struct aliases_list *aliases,
    char *pattern)
{
  if (!aliases)
    return NULL;
  while (aliases && strcmp(aliases->pattern, pattern))
    aliases = aliases->next;
  return aliases;
}

// TODO
static struct functions_list *find_function(struct functions_list *functions,
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
 * @return           index of the desired variable, -1 if not found
 * or -2 on error
 */
static int find_variable(struct variables_list *variables,
    char *name)
{
  if (!variables)
    return -2;
  for (size_t i = 0; i < variables->size; i++)
  {
    char *key = variable_get_key(variables->list[i]);
    if (!key)
      return -2;
    if (strcmp(key, name) == 0)
      return i;
    free(key);
  }
  return -1;
}

// TODO
int add_alias(struct shell_env *env, char *pattern, char *alias)
{
  if (!(env && alias && pattern && strlen(pattern)))
    return 1; //error
  struct aliases_list *aliases_list = find_alias(env->aliases, pattern);
  if (!aliases_list)
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
  struct functions_list *function = find_function(env->functions, name);
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

static int env_var_list_push_back(struct shell_env *env, char *keyvalue)
{
  if (!env || !env->variables)
    return -1;
  struct variables_list *vars = env->variables;
  if (vars->size == vars->capacity)
  {
    char **tmp = realloc(vars->list, vars->capacity * 2 * sizeof(char*));
    if (!tmp)
      return -1;
    vars->list = tmp;
    vars->capacity *= 2;
  }
  vars->list[vars->size++] = keyvalue;
  return 0;
}

static int env_var_list_update_var(struct shell_env *env, int index,
                                   char *keyvalue)
{
  if (!env || !env->variables)
    return -1;
  struct variables_list *vars = env->variables;
  free(vars->list[index]);
  vars->list[index] = keyvalue;
  return 0;
}
/**
 * add variable to the variable list of shell environment
 * @param  env   shell environment
 * @param  name  key of the variable
 * @param  value value of the variable
 * @return       1 if variable has been inserted, -1 otherwise
 */
int add_variable(struct shell_env *env, char *name, char *value)
{
  if (!env || !name || !strlen(name))
    return -1; // error
  int var_idx = find_variable(env->variables, name);
  if (var_idx == -2) // real error, not just not found
    return -1;
  char *keyvalue = malloc(strlen(name) + 1 + strlen(value));
  if (!keyvalue)
    return -1;
  strcpy(keyvalue, name);
  strcat(name, "=");
  strcat(name, value);
  if (var_idx < 0)
    return env_var_list_push_back(env, keyvalue);
  return env_var_list_update_var(env, var_idx, keyvalue);
}

// TODO
int remove_alias(struct shell_env *env, char *pattern);
// TODO
int remove_function(struct shell_env *env, char *name);
int remove_variable(struct shell_env *env, char *name);
