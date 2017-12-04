#ifndef PARSER_4_H
#define PARSER_4_H

#include "ast.h"

struct ast *parse_rule_if(int *return_value);
struct ast *parse_else_clause(int *return_value);
struct ast *parse_do_group(int *return_value);
struct ast *parse_case_clause(int *return_value);
struct ast *parse_case_item(int *return_value);

#endif /* PARSER_4_H */
