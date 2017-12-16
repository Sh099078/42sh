#include <stdio.h>

#include "ast_printer.h"

static char *get_type2(int x)
{
  switch(x)
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
    case CASE_ITEM:
      return "CASE_ITEM";
    case WORD:
      return "WORD";
    case ASSIGNMENT_WORD:
      return "ASSIGNMENT_WORD";
    case SEGFAULT:
      return "DEFAULT";
  }
  return NULL;
}

static char *type_to_char(int x)
{
  switch(x)
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
      return get_type2(x);
  }
  return NULL;
}

void *to_void(void *ast)
{
  return ast;
}

static void nodes_to_dot(struct ast *ast, FILE *f)
{
  if (!ast)
    return;

  fprintf(f, "\"%p\" [label=\"%s\"\n", to_void(ast), type_to_char(ast->type));
  for (size_t i = 0; i < ast->nb_children; i++)
  {
    if (ast->type != ELEMENT && ast->type != PREFIX)
      nodes_to_dot(ast->children[i], f);
    else
      fprintf(f, "\"%p\" [label=\"%s\"]\n", to_void(ast->children[0]), ast->values[0]);
    fprintf(f, "\"%p\" -> \"%p\"\n", to_void(ast), to_void(ast->children[i]));
  }
}

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
