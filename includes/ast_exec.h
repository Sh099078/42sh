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
#include "string.h"

int ast_exec(struct shell_env *env, struct ast *ast);
int simple_command(struct shell_env *env, struct ast *ast);
int and_or(struct shell_env *env, struct ast *ast);
int rule_if(struct shell_env *env, struct ast *ast);
int rule_for(struct shell_env *env, struct ast *ast);
int rule_while(struct shell_env *env, struct ast *ast);
int rule_until(struct shell_env *env, struct ast *ast);

#endif /* AST_EXEC_H */
