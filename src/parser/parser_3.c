#include <stdlib.h>

#include "parser.h"

struct ast *parse_compound_list(int *return_value, struct context *context);
struct ast *parse_rule_for(int *return_value, struct context *context);
struct ast *parse_rule_while(int *return_value, struct context *context);
struct ast *parse_rule_until(int *return_value, struct context *context);
struct ast *parse_rule_case(int *return_value, struct context *context);
