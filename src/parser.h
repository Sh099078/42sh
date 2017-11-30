#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

/*
** Tries to create a valid ast from the char* command.
** On success, returns a pointer on the created ast and sets *return_value
** to 0 ; on failure, sets *return_value to the correct error number and
** returns NULL.
*/
struct ast *parse_cmd(/*FILE input, */char *command, int *return_value);

#endif /* PARSER_H */
