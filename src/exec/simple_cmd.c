#include "ast_exec.h"


char **cmd_get_args(struct ast *ast, size_t start)
{
  char **argv = malloc(sizeof(char*) * (ast->nb_children - start + 1));
  if (!argv)
    return NULL;
  argv[0] = ast->value;
  for (size_t i = 0; i < ast->nb_children; i++)
    argv[i + 1] = ast->children[i + start]->value;
  return argv;
}

char *cmd_get_path(char *cmd_name)
{
  char *path = malloc(sizeof("/bin/") + strlen(cmd_name));
  if (!path)
    return NULL;
  strcpy(path, "/bin/");
  path = strcat(path, cmd_name);
  return path;
}

int exec_simple_command(struct ast *ast)
{
  size_t cmd_idx = 0; // TODO check optional variables before cmd
  char **argv = cmd_get_args(ast, cmd_idx);
  if (!argv)
    return 1; // TODO ERROR EXIT CODE
  char *path = cmd_get_path(ast->value);
  if (!path)
  {
    free(argv);
    return 1; // TODO EXIT CODE
  }
  pid_t pid = fork();
  if (pid == 0)
  {
    execv(path, argv);
  }
  else if (pid < 0)
  {
    warn("%s execution failed: could not fork:");
    return 1; // TODO check SCL exit code
  }
  int status = -1;
  waitpid(pid, &status, WEXITED);
  free(argv);
  free(path);
  return status;
}
