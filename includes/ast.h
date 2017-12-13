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
  CASE_ITEM,
  WORD
};

enum token_type
{
  NEW_LINE,
  IO_NUMBER,
  TOKEN,
  /* Operators */
  AND_IF,    // '&&'
  OR_IF,     // '||'
  DSEMI,     // ';;'
  DLESS,     // '<<'
  DGREAT,    // '>>'
  LESSAND,   // '<&'
  GREATAND,  // '>&'
  LESSGREAT, // '<>'
  DLESSDASH, // '<<-'
  CLOBBER,   // '>|'
  /* Reserved words */
  If,      // 'if'
  Then,    // 'then'
  Else,    // 'else'
  Elif,    // 'elif'
  Fi,      // 'fi'
  Do,      // 'do'
  Done,    // 'done'
  Case,    // 'case'
  Esac,    // 'esac'
  While,   // 'while'
  Until,   // 'until'
  For,     // 'for'
  Lbrace,  // '{'
  Rbrace,  // '}'
  Bang,    // '!'
  In       // 'in'
};

struct token
{
  enum token_type type;
  char *token;
};

struct ast
{
  char **values;
  enum node_type type;
  size_t nb_children;
  size_t capacity;
  struct ast **children;
};

struct ast *ast_init();
void ast_destroy(struct ast *ast);
int ast_add_child(struct ast *parent, struct ast *child, char *value);

/* The struct context is used during the parsing to keep in memory
** the current token and command so that on lexer or parser failure
** because of an end of input (without syntax error), the parser
** is able to ask for more input and continue creating the ast.
*/
struct context
{
  struct token *token;
  char *line;
  size_t token_size;
  size_t line_index;
  int first_line;
};

#endif /* AST_H */
