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

static char *get_type1(int x)
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

static FILE *ast_children(struct ast *ast, FILE *file)
{
  char *data;
  void *tmp_ast = ast;
  void *tmp_chili;
  if(ast->nb_children == 0)
  {
    for(int i = 0 ; ast->values[i] ; i++)
    {
      tmp_chili = &ast->values[i];
      fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_chili, ast->values[i]);
      fprintf(file, "\"%p\" -> \"%p\"\n", tmp_ast, tmp_chili);
    }
  }
  else
  {
    data = get_type1(ast->type);
    fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_ast, data);
    for(size_t i = 0 ; i < ast->nb_children ; i++)
    {
      tmp_chili = ast->children[i];
      data = get_type1(ast->children[i]->type);
      fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_chili, data);
      fprintf(file, "\"%p\" -> \"%p\"\n", tmp_ast, tmp_chili);
      file = ast_children(ast->children[i], file);
    }
  }
  return file;
}

void ast_to_dot(struct ast *ast)
{
  FILE *file = fopen("ast.dot", "w+");
  fprintf(file, "digraph G {\n");
  char *data;
  void *tmp_ast = ast;
  if(ast && ast->nb_children == 0)
  {
    data = get_type1(ast->type);
    fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_ast, data);
  }
  else if(ast)
    file = ast_children(ast, file);
  fprintf(file, "}");
  fclose(file);
}
