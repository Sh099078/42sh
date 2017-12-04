#ifndef PARSER_1_H
#define PARSER_1_H

#include "ast.h"

struct ast *parse_list(int *return_value);
struct ast *parse_and_or(int *return_value);
struct ast *parse_pipeline(int *return_value);
struct ast *parse_command(int *return_value);
struct ast *parse_simple_command(int *return_value);

#endif /* PARSER_1_H */
