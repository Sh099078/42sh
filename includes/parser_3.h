#ifndef PARSER_3_H
#define PARSER_3_H

/**
** \file parser_3.h
** \brief The functions responsible of parsing an ast from the input (4).
** \author Loup Federico
** \version 1.0
**/

#include "ast.h"

/**
**  This function parses the 'compound_list' rule of the grammar.
**/
struct ast *parse_compound_list(int *return_value, struct context *context);

/**
**  This function parses the 'rule_for' rule of the grammar.
**/
struct ast *parse_rule_for(int *return_value, struct context *context);

/**
**  This function parses the 'rule_while' rule of the grammar.
**/
struct ast *parse_rule_while(int *return_value, struct context *context);

/**
**  This function parses the 'rule_until' rule of the grammar.
**/
struct ast *parse_rule_until(int *return_value, struct context *context);

/**
**  This function parses the 'rule_case' rule of the grammar.
**/
struct ast *parse_rule_case(int *return_value, struct context *context);

#endif /* PARSER_3_H */
