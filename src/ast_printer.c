#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

FILE *ast_children(struct ast *ast, FILE *file)
{
  for(int i = 0 ; i < ast->nb_children ; i++)
  {
    fprintf(file, ast->value);
    fprintf(file, " -> ");
    fprintf(file, ast->children[i]->value);
    fprintf(file, ";\n");
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
  struct ast *asta = malloc(sizeof(struct ast));
  asta->value = malloc(sizeof(char *));
  asta->value = "a";
  asta->type = RULE_IF;
  asta->nb_children = 2;
  asta->children = malloc(sizeof(struct ast *));
  struct ast *astb = malloc(sizeof(struct ast));
  astb->value = malloc(sizeof(char *));
  astb->value = "b";
  astb->type = RULE_IF;
  astb->nb_children = 0;
  astb->children = NULL;
  struct ast *astc = malloc(sizeof(struct ast));
  astc->value = malloc(sizeof(char *));
  astc->value = "c";
  astc->type = RULE_IF;
  astc->nb_children = 0;
  astc->children = NULL;
  struct ast *astd = malloc(sizeof(struct ast));
  astd->value = malloc(sizeof(char *));
  astd->value = "d";
  astd->type = RULE_IF;
  astd->nb_children = 0;
  astd->children = NULL;
  struct ast *aste = malloc(sizeof(struct ast));
  aste->value = malloc(sizeof(char *));
  aste->value = "e";
  aste->type = RULE_IF;
  aste->nb_children = 0;
  aste->children = NULL;
  struct ast *astf = malloc(sizeof(struct ast));
  astf->value = malloc(sizeof(char *));
  astf->value = "f";
  astf->type = RULE_IF;
  astf->nb_children = 0;
  astf->children = NULL;
  asta->children[0] = astb;
  asta->children[1] = astc;
  astb->children[0] = astd;
  astd->children[0] = aste;
  astb->children[1] = astf;
  ast_to_dot(asta);
}