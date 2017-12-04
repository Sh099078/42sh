#include <stdlib.h>

#include "parser_3.h"

struct ast *parse_compound_list(int *return_value);
struct ast *parse_rule_for(int *return_value);
struct ast *parse_rule_while(int *return_value);
struct ast *parse_rule_until(int *return_value);
struct ast *parse_rule_case(int *return_value);
