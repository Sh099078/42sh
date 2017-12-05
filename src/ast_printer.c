#include "ast.h"
#include <stdio.h>
#include <stdlib.h>


char *get_type1(int x)
{
  switch(x)
  {
    case 0:
      return "INPUT";
    case 1:
      return "LIST";
    case 2:
      return "AND_OR";
    case 3:
      return "PIPELINE";
    case 4:
      return "COMMAND"
    case 5:
      return "SIMPLE_COMMAND";
    case 6:
      return "SHELL_COMMAND";
    case 7:
      return "FUNCDEF";
    case 8:
      return "REDIRECTION";
    case 9:
      return "PREFIX";
  }
}

char *get_type2(int x)
{
  switch(x)
  {
    case 10:
      return "ELEMENT";
    case 11:
      return "COMPOUND_LIST";
    case 12:
      return "RULE_FOR";
    case 13:
      return "RULE_WHILE";
    case 14:
      return "RULE_UNTIL";
    case 15:
      return "RULE_CASE";
    case 16:
      return "RULE_IF";
    case 17:
      return "ELSE_CLAUSE";
    case 18:
      return "DO_GROUP";
    case 19:
      return "CASE_CLAUSE";
    case 20:
      return"CASE_ITEM";
  }
}


FILE *ast_children(struct ast *ast, FILE *file)
{
  for(int i = 0 ; i < ast->nb_children ; i++)
  {
    fprintf(file, "%s", ast->value);
    fprintf(file, " -> ");
    fprintf(file, "%s", ast->children[i]->value);
    fprintf(file, ";\n");
    file = ast_children(ast->children[i], file);
  }
  return file;
}

void ast_to_dot(struct ast *ast)
{
  FILE *file = fopen("ast.dot", "w+");
  fprintf(file, "digraph G {\n");
  file = ast_children(ast, file);
  fprintf(file, "}");
  fclose(file);
}

int main()
{
  struct ast *ast = malloc(sizeof(struct ast));
  ast->type = ELEMENT;
  int x = ast->type;
  printf("%d", x);
}
