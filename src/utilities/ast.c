#include <stdlib.h>

#include "ast.h"

struct ast *ast_init()
{
  struct ast *ast = malloc(sizeof(struct ast));
  if (!ast)
    return NULL;
  ast->capacity = 2;
  ast->children = malloc(sizeof(struct ast *) * ast->capacity);
  char **values = malloc(sizeof(char *) * ast->capacity);
  if (!(ast->children && values))
  {
    if (ast)
      free(ast);
    if (values)
      free(values);
    return NULL;
  }
  ast->values = values;
  ast->type = SEGFAULT;
  ast->nb_children = 0;
  return ast;
}

void ast_destroy(struct ast *ast)
{
  if (!ast)
    return;
  for (size_t i = 0; i < ast->nb_children; i++)
  {
    if (ast->values[i])
      free(ast->values[i]);
    ast_destroy(ast->children[i]);
  }
  if (ast->children)
    free(ast->children);
  if (ast->type == WORD || ast->type == PREFIX)
    free(ast->values[0]);
  if (ast->values)
    free(ast->values);
  free(ast);
}

int ast_add_child(struct ast *ast, struct ast *new_child, char *value)
{
  if (!(ast && new_child))
    return 0;
  if (ast->nb_children == ast->capacity)
  {
    struct ast **new_children = realloc(ast->children,
        sizeof(struct ast*) * ast->capacity * 2);
    char **new_values = realloc(ast->values,
        sizeof(char *) * ast->capacity * 2);
    if (!(new_children && new_values))
    {
      if (new_values)
        free(new_values);
      if (new_children)
        free(new_children);
      return 0;
    }
    ast->children = new_children;
    ast->values = new_values;
    ast->capacity *= 2;
  }
  ast->children[ast->nb_children] = new_child;
  ast->values[ast->nb_children++] = value;

  return 1;
}
