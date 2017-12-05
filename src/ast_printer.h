#ifndef AST_PRINTER_H
#define AST_PRINTER_H

FILE *ast_children(struct ast *ast, FILE *file);
void ast_to_dot(struct ast *ast);

#endif /* AST_PRINTER_H */
