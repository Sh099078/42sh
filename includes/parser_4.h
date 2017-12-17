#ifndef PARSER_4_H
#define PARSER_4_H

/**
** \file parser_4.h
** \brief The functions responsible of parsing an ast from the input (5).
** \author Loup Federico
** \version 1.0
**/

#include "ast.h"

/**
**  This function parses the 'rule_if' rule of the grammar.
**/
struct ast *parse_rule_if(int *return_value, struct context *context);

/**
**  This function parses the 'else_clause' rule of the grammar.
**/
struct ast *parse_else_clause(int *return_value, struct context *context);

/**
**  This function parses the 'do_group' rule of the grammar.
**/
struct ast *parse_do_group(int *return_value, struct context *context);

/**
**  This function parses the 'case_clause' rule of the grammar.
**/
struct ast *parse_case_clause(int *return_value, struct context *context);

/**
**  This function parses the 'case_item' rule of the grammar.
**/
struct ast *parse_case_item(int *return_value, struct context *context);

#endif /* PARSER_4_H */
