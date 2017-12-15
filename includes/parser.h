#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h" //so that we don't have to include it 15x
#include "parser_1.h"
#include "parser_2.h"
#include "parser_3.h"
#include "parser_4.h"

struct ast *abort_parsing(struct ast *ast, int *return_value);

/*
** Tries to create a valid ast from the char* command.
** On success, returns a pointer on the created ast and sets *return_value
** to 0 ; on failure, sets *return_value to the correct error number and
** returns NULL.
*/
struct ast *ast_create(int *return_value);

struct ast *parse_input(int *return_value, struct context *context);

#endif /* PARSER_H */
