#ifndef AST_EXEC_H
#define AST_EXEC_H

/**
** @file ast_exec.h
** @brief AST execution functions
** @author Rod Guillaume, Hamza Mebarek
** @version 1.0
** @date 2017-12-17
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
** @file ast_exec.h
** @brief AST execution and rules functions
** @author Rod Guillaume & Hamza Mebarek
** @version 1.0
*/

#include "ast.h"
#include "struct.h"
#include "string.h"

/**
** Executes an AST representing a shell input
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     0 on success, error code otherwise (> 0)
*/
int ast_exec(struct shell_env *env, struct ast *ast);

/**
** Executes an INPUT type AST node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     exit status of the execution
*/
int input(struct shell_env *env, struct ast *ast);

/**
** Executes a LIST type AST node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     0 on success, error code otherwise (> 0)
*/
int list(struct shell_env *env, struct ast *ast);

/**
** Executes a PIPELINE AST node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     exit status of the last executed command
*/
int pipeline(struct shell_env *env, struct ast *ast);

/**
** Executes a SIMPLE_COMMAND type node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     exit status of the executed command
*/
int simple_command(struct shell_env *env, struct ast *ast);

/**
** Executes a AND_OR AST node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     exit status of the last executed command
*/
int and_or(struct shell_env *env, struct ast *ast);

/**
** Executes a RULE_IF AST node
** @param  env shell environment structure
** @param  ast AST node to execute
** @return The exit status of the if command will be the exit status of the
** then or else compound-list that was executed, or zero, if none was executed.
*/
int rule_if(struct shell_env *env, struct ast *ast);

/**
** Calls case_clause() on all children of the given tree
** Gets the case from the value of the first children's first value and calls
** case_clause through all the children to match the case itself.
** @param  the environment env, the tree ast we want to check
** @return  0 if no case matches, else returns 1
*/
int rule_case(struct shell_env *env, struct ast *ast);

/**
** Executes a RULE_FOR AST node
** First child is sequence to iterate on, the second is the variable key, and
** the third child is the compound_list to execute
** @param  env shell environment structure
** @param  ast AST node to execute
** @return     exit status of the last executed command, or 0 if loop was
** not executed
*/
int rule_for(struct shell_env *env, struct ast *ast);

/**
** Executes a RULE_WHILE AST node
** The compound-list-1 will be executed, and if it has a non-zero exit status,
** the while command will complete. Otherwise, the compound-list-2 will be
** executed, and the process will repeat.
** @param  env shell environment structure
** @param  ast AST node to execute
** @return  The exit status of the while loop will be the exit status of the
** last compound-list-2 executed, or zero if none was executed.
*/
int rule_while(struct shell_env *env, struct ast *ast);

/**
** Executes a RULE_UNTIL AST node
** The compound-list-1 will be executed, and if it has a zero exit status,
** the until command will complete. Otherwise, the compound-list-2 will be
** executed, and the process will repeat.
** @param  env shell environment structure
** @param  ast AST node to execute
** @return  The exit status of the until loop will be the exit status of the
** last compound-list-2 executed, or zero if none was executed.
*/
int rule_until(struct shell_env *env, struct ast *ast);

#endif /* AST_EXEC_H */
