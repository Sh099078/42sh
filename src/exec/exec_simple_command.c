#include "exec_rules.h"

int exec_simple_command(struct ast *ast)
{
  for (size_t i = 0; i < ast->nb_children; i++)
  {
    char **argv = get_args(ast);
    execv(ast->children[0]->value, argv)
    free(argv);
  }
}
