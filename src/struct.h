#ifndef STRUCT_H
#define STRUCT_H

struct shell_env
{
  struct aliases_lst *aliases;
  struct functions_lst *functions;
  struct variables_lst *variables;
};

struct aliases_lst
{
  char *pattern; //pattern to be identified as an alias.
  char *alias; //string to substitute to the pattern.
  struct str_lst *next;
};

struct functions_lst
{
  char *name;
  struct ast *ast;
  struct ast_lst *next;
};

struct variables_lst
{
  char *name;
  char *value;
  struct var_lst *next;
};

struct shell_env *shell_env_init(void);
int add_alias(struct shell_env *env, char *pattern, char *alias);
int add_function(struct shell_env *env, char *name, struct ast *ast);
int add_variable(struct shell_env *env, char *name, char *value);
int remove_alias(struct shell_env *env, char *pattern);
int remove_function(struct shell_env *env, char *name);
int remove_variable(struct shell_env *env, char *name);

#endif /* STRUCT_H */
