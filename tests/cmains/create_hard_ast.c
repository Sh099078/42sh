#include "create_hard_ast.h"

struct ast *create_simple_cmd_ast(int argc, char **argv)
{
  struct ast *ast = ast_init();
  ast->values = NULL;
  ast->type = SIMPLE_COMMAND;
  ast->nb_children = argc - 1;
  free(ast->children);
  ast->children = malloc(sizeof(struct ast*) * argc - 1);

  for (int i = 1; i < argc; i++)
  {
    struct ast *child = ast_init();
    child->values = malloc(sizeof(char*));
    child->values[0] = argv[i];
    child->nb_children = 1;
    ast->children[i - 1] = child;
  }
  return ast;
}

struct ast *create_and_or_ast(int argc, char **argv)
{
  argc = argc;
  argv = argv;
  return NULL;
}
