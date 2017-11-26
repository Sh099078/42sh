#ifndef AST_H
#define AST_H

enum node_type
{
  INPUT,
  LIST,
  AND_OR,
  PIPELINE,
  COMMAND,
  SIMPLE_COMMAND,
  SHELL_COMMAND,
  FUNCDEF,
  REDIRECTION,
  PREFIX,
  ELEMENT,
  COMPOUND_LIST,
  RULE_FOR,
  RULE_WHILE,
  RULE_UNTIL,
  RULE_CASE,
  RULE_IF,
  ELSE_CLAUSE,
  DO_GROUP,
  CASE_CLAUSE,
  CASE_ITEM
};

struct ast_node
{
  size_t nb_args;
  char **args;
  enum node_type type;
};

struct ast
{
  struct ast_node *value;
  size_t nb_children;
  struct ast child[];
};

#endif /* AST_H */
