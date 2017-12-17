#include <stdio.h>

#include "ast_printer.h"

static char *yeaiiiiyeaah(enum node_type type)
{
  switch (type)
  {
    case CASE_ITEM:
      return "CASE_ITEM";
    case WORD:
      return "WORD";
    case ASSIGNMENT_WORD:
      return "ASSIGNMENT_WORD";
    case SEGFAULT:
      return "DEFAULT";
    default:
      return "UNKNOWN";
  };
}

static char *the_enum_must_go_on(enum node_type type)
{
  switch (type)
  {
    case ELEMENT:
      return "ELEMENT";
    case COMPOUND_LIST:
      return "COMPOUND_LIST";
    case RULE_FOR:
      return "RULE_FOR";
    case RULE_WHILE:
      return "RULE_WHILE";
    case RULE_UNTIL:
      return "RULE_UNTIL";
    case RULE_CASE:
      return "RULE_CASE";
    case RULE_IF:
      return "RULE_IF";
    case ELSE_CLAUSE:
      return "ELSE_CLAUSE";
    case DO_GROUP:
      return "DO_GROUP";
    case CASE_CLAUSE:
      return "CASE_CLAUSE";
    default:
      return yeaiiiiyeaah(type);
  };
}

/**
 * Make a conversion of type into char * from the enum node_type
 * Takes a node_type as a parameter and according to its value, makes a
 * conversion of it into a char * which can be used when printing.
 * @param  node_type type which is the type of the ast
 * @return  the type of the node as a string
 */
static char *type_to_char(enum node_type type)
{
  switch (type)
  {
    case INPUT:
      return "INPUT";
    case LIST:
      return "LIST";
    case AND_OR:
      return "AND_OR";
    case PIPELINE:
      return "PIPELINE";
    case COMMAND:
      return "COMMAND";
    case SIMPLE_COMMAND:
      return "SIMPLE_COMMAND";
    case SHELL_COMMAND:
      return "SHELL_COMMAND";
    case FUNCDEF:
      return "FUNCDEF";
    case REDIRECTION:
      return "REDIRECTION";
    case PREFIX:
      return "PREFIX";
    default:
      return the_enum_must_go_on(type);
  };
}

/**
 * Convert any type of pointer to a void pointer
 * Takes a pointer (in this case a struct *ast) and converts casts it into
 * a void pointer
 * @param  the pointer that mush be casted
 * @return  the pointer casted into a void *
 */
static void *to_void(void *ast)
{
  return ast;
}

/**
 * Fill a .dot file with the tree information
 * Takes an ast and prints its content into a .dot file according of course to
 * the dot syntax and reprsenting every node with its data and its links with
 * other nodes.
 * @param  struct ast *ast the tree which should have its info written into the
 * .dot file represented by File *f
 * @return  a void as it only fills the file and doesn't have to return anything
 */
static void nodes_to_dot(struct ast *ast, FILE *f)
{
  if (!ast)
    return;

  if (ast->type != WORD && ast->type != ASSIGNMENT_WORD)
    fprintf(f, "\"%p\" [label=\"%s\"]\n", to_void(ast), type_to_char(ast->type));
  else
    fprintf(f, "\"%p\" [label=\"%s\"]\n", to_void(ast), ast->values[0]);

  for (size_t i = 0; i < ast->nb_children; i++)
  {
    if (ast->type != WORD && ast->type != ASSIGNMENT_WORD)
      nodes_to_dot(ast->children[i], f);
    fprintf(f, "\"%p\" -> \"%p\"\n", to_void(ast), to_void(ast->children[i]));
  }
}

/**
 * Creates a .dot file and fills via nodes_to_dot()
 * This will basically create the .dot file and call nodes_to_dot on the tree
 * @param  struct ast *ast which is the tree we want to convert into a dot file
 * @return  a void as it creates the .dot file and is not expected to return
 */
void ast_to_dot(struct ast *ast)
{
  FILE *file = fopen("ast.dot", "w+");
  if (!file)
    return;
  fprintf(file, "digraph G {\n");
  nodes_to_dot(ast, file);
  fprintf(file, "}");
  fclose(file);
}
