#include "ast.h"
#include "ast_printer.h"


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
      return "COMMAND";
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
      return "CASE_ITEM";
    case 21:
      return "WORD";
  }
}

FILE *ast_children(struct ast *ast, FILE *file)
{
  char *type;
  char *value;
  for(int i = 0 ; i < ast->nb_children ; i++)
  {
    if(ast->type <10)
      type = get_type1(ast->type);
    else if(ast->type < 22)
      type = get_type2(ast->type);
    value = ast->value;
    fprintf(file, "\"%p\" [label=\"%s : %s\"]\n", ast, type, value); 
    if(ast->children[i]->type <10)
      type = get_type1(ast->children[i]->type);
    else if(ast->type < 22)
      type = get_type2(ast->children[i]->type);
    value = ast->children[i]->value;
    fprintf(file, "\"%p\" [label=\"%s : %s\"]\n", ast->children[i], type, value);
    fprintf(file, "\"%p\" -> \"%p\"\n", ast, ast->children[i]);
    file = ast_children(ast->children[i], file);
  }
  return file;
}

void ast_to_dot(struct ast *ast)
{
  FILE *file = fopen("ast.dot", "w+");
  fprintf(file, "digraph G {\n");
  char *type;
  char *value;
  if(ast && ast->nb_children == 0)
  {
    if(ast->type <10)
      type = get_type1(ast->type);
    else if(ast->type < 22)
      type = get_type2(ast->type);
    value = ast->value;
    fprintf(file, "\"%p\" [label=\"%s : %s\"]\n", ast, type, value); 
  }
  else if(ast)
    file = ast_children(ast, file);
  fprintf(file, "}");
  fclose(file);
}
