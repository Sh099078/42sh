#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

/*
** Tries to create a valid ast from the char* command.
** On success, returns a pointer on the created ast and sets *return_value
** to 0 ; on failure, sets *return_value to the correct error number and
** returns NULL.
*/
struct ast *ast_create(int *return_value);

struct ast *parse_input(int *return_value, struct context *context);

#endif /* PARSER_H */
