#include "ast_exec.h"

int ast_exec(struct shell_env *env, struct ast *ast)
{
  size_t dispatch_len = SEGFAULT; // last enum element
  int (*func[])(struct shell_env*, struct ast*) =
  {
    input, list, and_or, pipeline, 0, simple_command, 0,
    0, 0, 0, 0, 0, rule_for,
    rule_while, rule_until, 0, rule_if, 0, 0, 0, 0, 0, 0, 0
  };
  for (size_t i = 0; i < dispatch_len; i++)
  {
    if (ast->type == i)
    {
      if (func[i])
        return func[i](env, ast);
      else
        break;
    }
  }
  warnx("AST TYPE %d not handled yet", ast->type);
  return 1;
}
