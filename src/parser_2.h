#ifndef PARSER_2_H
#define PARSER_2_H

#include "ast.h"

struct ast *parser_shell_command(int *return_value);
struct ast *parse_funcdef(int *return_value);
struct ast *parse_redirection(int *return_value);
struct ast *parse_prefix(int *return_value);
struct ast *parse_element(int *return_value);

#endif /* PARSER_2_H */
