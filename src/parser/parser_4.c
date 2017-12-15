#include <stdlib.h>

#include "parser.h"

struct ast *parse_rule_if(int *return_value, struct context *context);
struct ast *parse_else_clause(int *return_value, struct context *context);
struct ast *parse_do_group(int *return_value, struct context *context);
struct ast *parse_case_clause(int *return_value, struct context *context);
struct ast *parse_case_item(int *return_value, struct context *context);
