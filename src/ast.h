#ifndef AST_H
#define AST_H

#include <stddef.h>

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

enum token_type
{
  WORD,
  OPERATOR
};

struct token
{
  enum token_type type;
  char *token;
};

struct ast
{
  char *value;
  enum node_type type;
  size_t nb_children;
  struct ast **children;
};

struct ast *ast_create();
void ast_destroy(struct ast *ast);
struct ast_node *ast_node_create();
void ast_node_destroy(struct ast_node *ast_node);

/* The struct context is used during the parsing to keep in memory
** the current token and command so that on lexer or parser failure
** because of an end of input (without syntax error), the parser
** is able to ask for more input and continue creating the ast.
*/
struct context
{
  struct token *token;
  char *command; //concatenation of n lines forming a command
  size_t token_size;
  size_t cmd_index;
};

#endif /* AST_H */
