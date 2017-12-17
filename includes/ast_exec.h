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

// TO MAKE STATIC AFTER TESTINGS
char **cmd_get_args(struct ast *ast, size_t start);
char *cmd_get_path(char *cmd_name);
// END TO MAKE STATIC

int ast_exec(struct shell_env *env, struct ast *ast);
int input(struct shell_env *env, struct ast *ast);
int list(struct shell_env *env, struct ast *ast);
int pipeline(struct shell_env *env, struct ast *ast);
int simple_command(struct shell_env *env, struct ast *ast);
int and_or(struct shell_env *env, struct ast *ast);
int rule_if(struct shell_env *env, struct ast *ast);
int rule_case(struct shell_env *env, struct ast *ast);

/**
 * Executes a bash style for loop
 * First child is sequence to iterate on, the second is the variable key, and
 * the third child is the compound_list to execute
 * @param  ast AST node corresponding to the for loop
 * @return     last command executed exit status on success,
 * an error code otherwise
 */
int rule_for(struct shell_env *env, struct ast *ast);

/**
 * The compound-list-1 will be executed, and if it has a non-zero exit status,
 * the while command will complete. Otherwise, the compound-list-2 will be
 * executed, and the process will repeat.
 * @param  ast node to evaluate in parsing AST
 * @return  The exit status of the while loop will be the exit status of the
 * last compound-list-2 executed, or zero if none was executed.
 */
int rule_while(struct shell_env *env, struct ast *ast);

/**
 * The compound-list-1 will be executed, and if it has a zero exit status,
 * the until command will complete. Otherwise, the compound-list-2 will be
 * executed, and the process will repeat.
 * @param  ast node to evaluate in parsing AST
 * @return  The exit status of the until loop will be the exit status of the
 * last compound-list-2 executed, or zero if none was executed.
 */
int rule_until(struct shell_env *env, struct ast *ast);

#endif /* AST_EXEC_H */
