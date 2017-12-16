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

// TODO nextToken + ast_incr_capacity
static int get_next_andor(char **argv)
{
  // argv is null terminated
}

static struct ast *ast_incr_capacity(struct ast *ast)
{
  ast = ast;
  return NULL;
}

struct ast *create_and_or_ast(int argc, char **argv)
{
  struct ast *ast = ast_init();
  // loop with i
  int nextCmd = 0; // next simple command index
  int nextAndOr = get_next_andor(argv); // get index of next && || operator
  int child = 0;
  while (nextAndOr > 0)
  {
    if (child == ast->capacity && !ast_incr_capacity(ast))
      return NULL;
    ast->children[child++] = create_simple_cmd_ast(nextAndOr, argv + nextCmd);
    nextCmd += nextAndOr;
    nextAndOr = get_next_andor(argv); // get index of next && || operator
  }
  return ast;
}
