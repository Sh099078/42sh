#ifndef PARSER_2_H
#define PARSER_2_H

/**
** \file ast.h
** \brief The functions responsible of parsing an ast from the input (3).
** \author Loup Federico
** \version 1.0
**/

#include "ast.h"

/**
**  This function parses the 'shell_command' rule of the grammar.
**/
struct ast *parser_shell_command(int *return_value, struct context *context);

/**
**  This function parses the 'funcdef' rule of the grammar.
**/
struct ast *parse_funcdef(int *return_value, struct context *context);

/**
**  This function parses the 'redirection' rule of the grammar.
**/
struct ast *parse_redirection(int *return_value, struct context *context);

/**
**  This function parses the 'parse_prefix' rule of the grammar.
**/
struct ast *parse_prefix(int *return_value, struct context *context);

/**
**  This function parses the 'parse_element' rule of the grammar.
**/
struct ast *parse_element(int *return_value, struct context *context);

#endif /* PARSER_2_H */
