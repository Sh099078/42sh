#ifndef OPTIONS_H
#define OPTIONS_H

/**
** @file options.h
** @brief 
** @author Rod Guillaume
** @version 0.5
** @date 2017-11-28
*/

#include <stddef.h>
#include <string.h>
#include <err.h>

/***
 * GNU long options
 *
 * When typing bash --version --help only the help is printed on stdout
 * Therefore, we'll just assume that only the last long option is really set
 *
 * TODO Ask an ACU
 */

/**
** @brief shopt built-in variables
*/
enum shopt_vars
{
  AST_PRINT = 1,
  DOTGLOB = 2,
  EXPAND_ALIASES = 4,
  EXTGLOB= 8,
  NOCASEGLOB = 16,
  NULLGLOB = 32,
  SOURCEPATH = 64,
  XPG_ECHO = 128
};

/**
** @brief options set when launching 42sh
*/
struct options
{
  char shopt_vars;
  char c;
  char norc;
  char version;
  char **files; // points to one argv's element (no free needed)
  size_t files_len;
};

struct options options_get(int argc, char *argv[]);

#endif /* OPTIONS_H */
