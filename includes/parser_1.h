#ifndef PARSER_1_H
#define PARSER_1_H

#include "ast.h"

/**
**  This function parses the 'list' rule of the grammar.
**/
struct ast *parse_list(int *return_value, struct context *context);

/**
** This function parses the 'and_or' rule of the grammar.
*/
struct ast *parse_and_or(int *return_value, struct context *context);

/**
**  This function parses the 'pipeline' rule of the grammar.
**/
struct ast *parse_pipeline(int *return_value, struct context *context);

/**
**  This function parses the 'command' rule of the grammar.
**/
struct ast *parse_command(int *return_value, struct context *context);

/**
**  This function parses the 'simple_command' rule of the grammar.
**/
struct ast *parse_simple_command(int *return_value, struct context *context);

#endif /* PARSER_1_H */
