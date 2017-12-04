#include <stdlib.h>

#include "parser_1.h"

struct ast *parse_input(int *return_value);
struct ast *parse_list(int *return_value);
struct ast *parse_and_or(int *return_value);
struct ast *parse_pipeline(int *return_value);
struct ast *parse_command(int *return_value);
