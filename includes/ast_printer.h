#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "ast.h"

/**
 * Creates a .dot file and fills via nodes_to_dot()
 * This will basically create the .dot file and call nodes_to_dot on the tree
 * @param  struct ast *ast which is the tree we want to convert into a dot file
 * @return  a void as it creates the .dot file and is not expected to return
 */
void ast_to_dot(struct ast *ast);

#endif /* AST_PRINTER_H */
