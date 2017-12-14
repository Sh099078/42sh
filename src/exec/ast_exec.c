#include "ast_exec.h"

int ast_exec(struct shell_env *env, struct ast *ast)
{
  ast = ast;
  switch (ast->type)
  {
  case AND_OR:
    return and_or(env, ast);
    break;
  case SIMPLE_COMMAND:
    return simple_command(env, ast);
    break;
  case RULE_FOR:
    return rule_for(env, ast);
    break;
  case RULE_WHILE:
    return rule_while(env, ast);
    break;
  case RULE_UNTIL:
    return rule_until(env, ast);
    break;
  case RULE_IF:
    return rule_if(env, ast);
    break;
  case INPUT:
  case RULE_CASE:
  case LIST:
  case PIPELINE:
  case COMMAND:
  case SHELL_COMMAND:
  case FUNCDEF:
  case REDIRECTION:
  case PREFIX:
  case ELEMENT:
  case DO_GROUP:
  case CASE_CLAUSE:
  case CASE_ITEM:
  case COMPOUND_LIST:
  default:
    warnx("AST TYPE %d not handled yet", ast->type);
    return 1;
    break;
  }
}
