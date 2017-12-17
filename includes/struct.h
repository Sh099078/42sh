#ifndef STRUCT_H
#define STRUCT_H

/**
** @file struct.h
** @brief Shell environment structure functions
** @author Loup Federico, Rod Guillaume
** @version 1.0
** @date 2017-12-17
*/

#include <string.h>
#include <stdlib.h>

/**
** shell environment structure containing variables, defined functions and
** aliases
*/
struct shell_env
{
  struct functions_list *functions;
  struct aliases_list* aliases;
  struct variables_list *variables;
};

/**
** aliases linked list structure
*/
struct aliases_list
{
  char *pattern; //pattern to be identified as an alias.
  char *alias; //string to substitute to the pattern.
  struct aliases_list *next;
};

/**
** function definitions linked list structure
*/
struct functions_list
{
  char *name;
  struct ast *ast;
  struct functions_list *next;
};

/**
** variables list (vector) structure
*/
struct variables_list
{
  char **list;
  size_t capacity;
  size_t size;
};

/**
** shell environment structure constructor
** @return  shell_env structure created or NULL on error
*/
struct shell_env *shell_env_init(void);

/**
** shell environment structure destructor
** @param env shell environment structure
*/
void shell_env_destroy(struct shell_env *env);

/**
** add alias to environment structure
** @param  env     environment structure
** @param  pattern command being aliased
** @param  alias   alias name
** @return 0 if successfully added, 1 otherwise
*/
int add_alias(struct shell_env *env, char *pattern, char *alias);

/**
** add function definition to environment structure
** @param  env     environment structure
** @param  name function name
** @param  ast   associated AST
** @return 0 if successfully added, 1 otherwise
*/
int add_function(struct shell_env *env, char *name, struct ast *ast);

/**
** add variable to the variable list of shell environment
** @param  env   shell environment
** @param  name  key of the variable
** @param  value value of the variable
** @return       1 if variable has been inserted, -1 otherwise
*/
int add_variable(struct shell_env *env, char *name, char *value);

/**
** removed alias from alias list
** @return 1 on success, 0 otherwise
*/
int remove_alias(struct shell_env *env, char *pattern);

/**
** remove function definition from function list
** @return 1 on success, 0 otherwise
*/
int remove_function(struct shell_env *env, char *name);

/**
** remove variable from variable list
** @return  1 on success, 0 otherwise
*/
int remove_variable(struct shell_env *env, char *name);

#endif /* STRUCT_H */
