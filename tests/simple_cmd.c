
#include <stdio.h>

int main(void)
{
  struct ast *ast = malloc(sizeof(struct ast));
  ast->children = malloc(sizeof(struct ast*) * 3);
  ast->value = "echo";
  ast->nb_children = 3;
  for (int i = 0; i < 3; i++)
  {
    struct ast *child = malloc(sizeof(struct ast));
    child->value = "arg";
    ast->children[i] = child;
  }
  char **args = cmd_get_args(ast, 0);
  char *path = cmd_get_path(args[0]);
  printf("%s :", path);
  for (size_t i = 0; i < 4; i++)
    printf("%s", args[i]);
  exec_simple_command(ast);
  return 0;
}
