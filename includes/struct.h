#ifndef STRUCT_H
#define STRUCT_H

#include <string.h>
#include <stdlib.h>

struct shell_env
{
  struct functions_list *functions;
  struct aliases_list* aliases;
  struct variables_list *variables;
};

struct aliases_list
{
  char *pattern; //pattern to be identified as an alias.
  char *alias; //string to substitute to the pattern.
  struct aliases_list *next;
};

struct functions_list
{
  char *name;
  struct ast *ast;
  struct functions_list *next;
};

struct variables_list
{
  char **list;
  size_t capacity;
  size_t size;
};

struct shell_env *shell_env_init(void);
void shell_env_destroy(struct shell_env *env);
int add_alias(struct shell_env *env, char *pattern, char *alias);
int add_function(struct shell_env *env, char *name, struct ast *ast);
int add_variable(struct shell_env *env, char *name, char *value);
int remove_alias(struct shell_env *env, char *pattern);
int remove_function(struct shell_env *env, char *name);
int remove_variable(struct shell_env *env, char *name);

#endif /* STRUCT_H */
