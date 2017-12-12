#ifndef LEXER_H
#define LEXER_H

#include "ast.h"

/*
** Returns 1 when able to retrieve the next token from input, 0 when it reaches
** the end of input or if memory is exhausted and it cannot malloc space to save
** the current token.
*/
int get_next_token(struct context *context);

#endif /* LEXER_H */
