#ifndef AST_EXEC_H
#define AST_EXEC_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ast.h"
#include "struct.h"

char **cmd_get_args(struct ast *ast, size_t start);
char *cmd_get_path(char *cmd_name);
int exec_simple_command(struct ast *ast);
int exec_and_or(struct ast *ast);
int exec_rule_if(struct ast *ast);
int ast_exec(struct ast *ast);
int rule_for(struct shell_env *env, struct ast *ast);

#endif /* AST_EXEC_H */
