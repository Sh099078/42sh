#ifndef LEXER_H
#define LEXER_H

#include "ast.h"

/*
** Reads the command input looking for the next token according to
** the SCL 2.3. The size_t *index indicates the first character
** that hasn't been used yet by get_next_token from the input.
** RETURN VALUE: A struct token containing the copy of the next
** token found in the input and its type.
*/
int get_next_token(struct context *context, struct token *token);

#endif /* LEXER_H */
