#ifndef LEXER_H
#define LEXER_H

/**
** \file lexer.h
** \brief Gives an interface for the parser to communicate with the lexer.
** \author Loup Federico
** \version 1.0
**/

#include "ast.h"

/*
** Returns 1 when able to retrieve the next token from input, 0 when it reaches
** the end of input or if memory is exhausted and it cannot malloc space to save
** the current token.
*/
int get_next_token(struct context *context);

#endif /* LEXER_H */
