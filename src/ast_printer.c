#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

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
