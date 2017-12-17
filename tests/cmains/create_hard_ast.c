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

static int get_next_andor(char **argv)
{
  // argv is null terminated
  int i = 0;
  while (argv[i] && (!strcmp(argv[i], "&&") || !strcmp(argv[i], "||")))
    i++;
  return argv[i] ? i : -1;
}

static struct ast *ast_incr_capacity(struct ast *ast)
{
  int new_capacity = ast->capacity * 2;
  void *tmp_children = realloc(ast->children,
                               sizeof(struct ast*) * new_capacity);
  if (!tmp_children)
    return NULL;
  void *tmp_values = realloc(ast->values,
                               sizeof(char*) * new_capacity);
  if (!tmp_values)
  {
    free(tmp_children);
    return NULL;
  }
  ast->capacity = new_capacity;
  ast->children = tmp_children;
  ast->values = tmp_values;
  return ast;
}

struct ast *create_and_or_ast(char **argv)
{
  struct ast *ast = ast_init();
  // loop with i
  size_t nextCmd = 0; // next simple command index
  size_t child = 0;
  int nextAndOr = get_next_andor(argv); // get index of next && || operator
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
