#include <stdlib.h>
#include "ast.h"
#include "struct.h"

struct ast *create_simple_cmd_ast(int argc, char **argv);
struct ast *create_and_or_ast(char **argv);
