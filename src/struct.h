#ifndef STRUCT_H
#define STRUCT_H

struct aliases_lst
{
  char *pattern; //pattern to be identified as an alias.
  char *alias //string to substitute to the pattern.
  struct str_lst *next;
};

struct functions_lst
{
  char *name;
  struct *ast *ast;
  struct ast_lst *next;
};

struct variables_lst
{
  char *name;
  char *value;
  struct var_lst *next;
};

#endif /* STRUCT_H */
