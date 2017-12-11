#include "ast_exec.h"

int ast_exec(struct ast *ast/*, int return_value*/)
{
  ast = ast;
  return 1; //added to make it compile
/*
  switch (ast->type)
  {
  case INPUT:
    return -1;
    break;
  case LIST:
    return -1;
    break;
  case AND_OR:
    return exec_and_or(ast);
    break;
  case PIPELINE:
    return exec_pipeline(ast);
    break;
  case COMMAND:
    return exec_command(ast);
    break;
  case SIMPLE_COMMAND:
    return exec_simple_command(ast);
    break;
  case SHELL_COMMAND:
    return exec_shell_command(ast);
    break;
  case FUNCDEF:
    return exec_funcdef(ast);
    break;
  case REDIRECTION:
    return exec_redirection(ast);
    break;
  case PREFIX:
    return exec_prefix(ast);
    break;
  case ELEMENT:
    return exec_element(ast);
    break;
  case COMPOUND_LIST:
    return exec_compound_list(ast);
    break;
  case RULE_FOR:
    return exec_rule_for(ast);
    break;
  case RULE_WHILE:
    return exec_rule_while(ast);
    break;
  case RULE_UNTIL:
    return exec_rule_until(ast);
    break;
  case RULE_CASE:
    return exec_rule_case(ast);
    break;
  case RULE_IF:
    return exec_rule_if(ast);
    break;
  case ELSE_CLAUSE:
    return exec_else_clause(ast);
    break;
  case DO_GROUP:
    return exec_do_group(ast);
    break;
  case CASE_CLAUSE:
    return exec_case_clause(ast);
    break;
  case CASE_ITEM:
    return exec_case_item(ast);
    break;
  }
*/
}
