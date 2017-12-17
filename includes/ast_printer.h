#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "ast.h"

static char *yeaiiiiyeaah(enum node_type type);
static char *the_enum_must_go_on(enum node_type type);

/**
 * Make a conversion of type into char * from the enum node_type
 * Takes a node_type as a parameter and according to its value, makes a
 * conversion of it into a char * which can be used when printing.
 * @param  node_type type which is the type of the ast
 * @return  the type of the node as a string
 */
static char *type_to_char(enum node_type type);

/**
 * Convert any type of pointer to a void pointer
 * Takes a pointer (in this case a struct *ast) and converts casts it into
 * a void pointer
 * @param  the pointer that mush be casted
 * @return  the pointer casted into a void *
 */
static void *to_void(void *ast);

/**
 * Fill a .dot file with the tree information
 * Takes an ast and prints its content into a .dot file according of course to
 * the dot syntax and reprsenting every node with its data and its links with
 * other nodes.
 * @param  struct ast *ast the tree which should have its info written into the
 * .dot file represented by File *f
 * @return  a void as it only fills the file and doesn't have to return anything
 */
static void nodes_to_dot(struct ast *ast, FILE *f);

/**
 * Creates a .dot file and fills via nodes_to_dot()
 * This will basically create the .dot file and call nodes_to_dot on the tree
 * @param  struct ast *ast which is the tree we want to convert into a dot file
 * @return  a void as it creates the .dot file and is not expected to return
 */
void ast_to_dot(struct ast *ast);

#endif /* AST_PRINTER_H */
