#ifndef OPTIONS_H
#define OPTIONS_H

/**
** @file options.h
** @brief Shell options parsing functions
** @author Rod Guillaume
** @version 1.0
** @date 2017-11-28
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <err.h>

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

/**
 * Parses options given to 42sh program
 * @param  argc size of the argv strings array
 * @param  argv strings array, containing all arguments given to 42sh
 * @return      options structure containing all the flags
 */
struct options options_get(int argc, char *argv[]);

#endif /* OPTIONS_H */
