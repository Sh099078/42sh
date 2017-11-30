#ifndef STRUCT_H
#define STRUCT_H

struct str_lst
{
  char *string;
  struct str_lst *next;
};

struct fct_lst
{
  char *name;
  struct *ast *ast;
  struct ast_lst *next;
};

struct var_lst
{
  char *name;
  char *value;
  struct var_lst *next;
};

#endif /* STRUCT_H */
