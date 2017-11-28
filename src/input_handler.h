#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdio.h>

/*
** Returns the next line line from the input.
** If the parsing or the lexor fail at building an ast
** with the returned line, the function returns the first
** returned line concatenated with the next line of the
** input, and so on until the end of input is reached
** or a valid AST has successfully been built.
*/
char *get_next_line(FILE *input, const char *curr_line);

#endif /* INPUT_HANDLER_H */
