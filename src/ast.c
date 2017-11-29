#include <stdlib.h>

#include "ast.h"

/*struct ast *ast_create()
{
  struct ast *ast = malloc(sizeof(struct ast));
  if (!ast)
    return NULL;
  ast->value = NULL;
  ast->nb_children = 0;
  ast->children = NULL;
  return ast;
}

void ast_destroy(struct ast *ast)
{
  if (!ast)
    return;
  ast_node_destroy(ast->value);
  for (size_t i = 0; i < ast->nb_children; i++)
    ast_destroy(ast->children[i]);
  free(ast);
}
struct ast_node *ast_node_create()
{
  struct ast_node *ast_node = malloc(sizeof(struct ast_node));
  if (!ast_node)
    return NULL;
  ast_node->nb_args = 0;
  ast_node->args = NULL;
  return ast_node;
}

void ast_node_destroy(struct ast_node *ast_node)
{
  if (!ast_node)
    return;
  if (ast_node->args)
    free(ast_node->args);
  free(ast_node);
}*/
