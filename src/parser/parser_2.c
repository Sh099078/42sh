#include <stdlib.h>

#include "parser_2.h"

struct ast *parser_shell_command(int *return_value, struct context *context);
struct ast *parse_funcdef(int *return_value, struct context *context);
struct ast *parse_redirection(int *return_value, struct context *context);
struct ast *parse_prefix(int *return_value, struct context *context);
struct ast *parse_element(int *return_value, struct context *context);
