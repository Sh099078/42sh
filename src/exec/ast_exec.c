#include "ast_exec.h"

int ast_exec(struct shell_env *env, struct ast *ast);
{
  ast = ast;
  return 1; //added to make it compile
  switch (ast->type)
  {

  case INPUT:
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
    warnx("AST TYPE %d not handled yet", ast->type);
    break;
  case AND_OR:
    return and_or(ast);
    break;
  case SIMPLE_COMMAND:
    return simple_command(ast);
    break;
  case RULE_FOR:
    return rule_for(ast);
    break;
  case RULE_WHILE:
    return rule_while(ast);
    break;
  case RULE_UNTIL:
    return rule_until(ast);
    break;
  case RULE_CASE:
    return rule_case(ast);
    break;
  case RULE_IF:
    return rule_if(ast);
    break;
  }
}
