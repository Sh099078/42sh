#include "../../includes/ast.h"
#include "../../includes/ast_printer.h"


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
  return NULL;
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
  return NULL;
}

/*FILE *ast_children(struct ast *ast, FILE *file)
{
  char *type;
  char *value;
  void *tmp_ast = ast;
  void *tmp_chili;
  for(size_t i = 0 ; i < ast->nb_children ; i++)
  {
    tmp_chili = ast->children[i];
    if(ast->type <10)
      type = get_type1(ast->type);
    else if(ast->type < 22)
      type = get_type2(ast->type);
    value = ast->values[0];
    fprintf(file, "\"%p\" [label=\"%s : %s\"]\n", tmp_ast, type, value);
    if(ast->children[i]->type <10)
      type = get_type1(ast->children[i]->type);
    else if(ast->type < 22)
      type = get_type2(ast->children[i]->type);
    value = ast->children[i]->values[0];
    fprintf(file, "\"%p\" [label=\"%s : %s\"]\n", tmp_chili, type, value);
    fprintf(file, "\"%p\" -> \"%p\"\n", tmp_ast, tmp_chili);
    file = ast_children(ast->children[i], file);
  }
  return file;
}*/


FILE *ast_children(struct ast *ast, FILE *file)
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
    if(ast->type <10)
      data = get_type1(ast->type);
    else if(ast->type < 22)
      data = get_type2(ast->type);
    fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_ast, data);
    for(size_t i = 0 ; i < ast->nb_children ; i++)
    {
      tmp_chili = ast->children[i];
      if(ast->children[i]->type < 10)
        data = get_type1(ast->children[i]->type);
      else if(ast->children[i]->type < 22)
        data = get_type2(ast->children[i]->type);
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
    if(ast->type <10)
      data = get_type1(ast->type);
    else if(ast->type < 22)
      data = get_type2(ast->type);
    fprintf(file, "\"%p\" [label=\"%s\"]\n", tmp_ast, data);
  }
  else if(ast)
    file = ast_children(ast, file);
  fprintf(file, "}");
  fclose(file);
}

int main()
{
  struct ast *asta = malloc(sizeof(struct ast));
  asta->type = INPUT;
  asta->nb_children = 3;
  asta->children = malloc(sizeof(struct ast *));

  struct ast *astb = malloc(sizeof(struct ast));
  astb->values = malloc(sizeof(char **));
  astb->values[0] = "cat";
  astb->values[1] = "a";
  astb->type = COMMAND;
  astb->nb_children = 0;

  struct ast *astc = malloc(sizeof(struct ast));
  astc->values = malloc(sizeof(char **));
  astc->values[0] = "cat";
  astc->values[1] = "b";
  astc->type = SIMPLE_COMMAND;
  astc->nb_children = 0;

  struct ast *astd = malloc(sizeof(struct ast));
  astd->values = malloc(sizeof(char **));
  astd->values[0] = "echo";
  astd->values[1] = "c";
  astd->type = COMMAND;
  astd->nb_children = 0;

  asta->children[0] = astb;
  asta->children[1] = astc;
  asta->children[2] = astd;
  ast_to_dot(asta);
  return 1;
}
