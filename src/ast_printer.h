#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <stdio.h>
#include <stdlib.h>

FILE *ast_children(struct ast *ast, FILE *file);
void ast_to_dot(struct ast *ast);

#endif /* AST_PRINTER_H */
