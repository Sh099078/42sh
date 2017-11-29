#include "options.h"

/**
 ** @brief Options constructor
 **
 ** @return initialized options structure
 */
static struct options options_create(void)
{
  struct options opts;
  opts.shopt_vars = 0;
  opts.c = 0;
  opts.norc = 0;
  opts.version = 0;
  opts.files = 0;
  opts.files_len = 0;
  return opts;
}

static int is_long_option(const char *opt)
{
  return strlen(opt) > 2 && !strncmp(opt, "--", 2);
}

/**
 ** @brief Checks if s could be a typo-ed opt string
 **
 ** @param s    hypothetically opt string with typos
 ** @param opt  valid option string
 **
 ** @return 1 if s was opt with typos, 0 otherwise
 */
static int is_beginning(const char *s, const char *opt)
{
  if (strlen(s) > strlen(opt))
    return 0;
  if (strcmp(s, opt))
    warnx("%s: invalid option, but interpreted as %s", s, opt);
  return 1;
}


/**
 ** @brief sub-function of options_get, taking care of long options
 */
static void options_long_get(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  const char *valid_opts[] = { "norc", "ast-print", "ver", "version", 0 };
  for (; *i < argc && is_long_option(argv[*i]); (*i)++)
  {
    const char *opt = argv[*i] + 2;
    if (valid_opts[0][0] == opt[0]
        && is_beginning(opt, valid_opts[0]))
      opts->norc = 1;
    else if (valid_opts[1][0] == opt[0]
        && is_beginning(opt, valid_opts[1]))
      opts->shopt_vars |= AST_PRINT;
    else if (!strcmp(opt, valid_opts[2]))
      opts->version = 1;
    else if (valid_opts[3][0] == opt[0] && strlen(opt) > strlen("ver")
        && is_beginning(opt, valid_opts[3]))
      opts->version = 1;
    else 
      errx(1, "%s: invalid option\n"
              "Usage: 42sh [GNU long options] [options] [file]", opt);
  }
}

/**
 ** @brief parse the -c bash option, once every short options have been seen
 */
static void options_c(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  // TODO
  argc = argc;
  argv = argv;
  opts = opts;
  i = i;
}

static void shopt_option_warn(const char *opt)
{
  // TODO
  opt = opt;
} 
static int is_shopt_option(const char *opt)
{
  // TODO
  shopt_option_warn(opt);
  opt = opt;
  return 1;
}

static void shopt_handle_option(const char *opt, int set,
                                struct options *opts)
{
  // TODO
  set = set;
  opt = opt;
  opts = opts;
}

static int is_short_option(const char *opt)
{
  return strlen(opt) > 1 && (opt[0] == '-' || opt[0] == '+');
}

/**
 ** @brief parse [-+]O option, setting shopt variables
 ** It only supports -s -u -q built-in options
 */
static void options_shopt(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  // TODO
  argc = argc;
  // -O sets the value, +O unsets it
  // if value does not exist, print all available values
  int is_set = argv[(*i)++][0] == '-';
  for (; !is_short_option(argv[*i]); (*i)++)
  {
    if (!is_shopt_option(argv[*i]))
      break;
    shopt_handle_option(argv[*i], is_set, opts);
  }
}

/**
 ** @brief Checks if opt was the '--' end of options signal
 */
static int is_end_option(const char *opt)
{
  return !opt[1] && opt[0] == '-';
}

/**
 ** @brief sub-function of options_get, taking care of short options
 */
static void options_short_get(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  // TODO
  argc = argc;
  argv = argv;
  opts = opts;
  i = i;
  int is_c_enabled = 0;
  for (; *i < argc && is_short_option(argv[*i]); (*i)++)
  {
    const char *opt = argv[*i] + 1;
    if (is_end_option(opt))
    {
      (*i)++;
      break;
    }
    if (!opt[1] && opt[0] == 'c')
      is_c_enabled = 1;
    else if (!opt[1] && opt[0] == 'O')
      // +-O option TODO
      options_shopt(argc, argv, opts, i);
    else
      errx(1, "%s: invalid option\n"
              "Usage: 42sh [GNU long options] [options] [file]", opt);
  }
  if (is_c_enabled)
  {
    // -c option string and files to handle, now that all options have been
    // done
    options_c(argc, argv, opts, i);
  }
}

/**
 ** @brief sub-function of options_get, taking care of files
 */
static void options_files_get(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  // TODO
  argc = argc;
  argv = argv;
  opts = opts;
  i = i;
}

struct options options_get(int argc, char *argv[])
{
  struct options opts = options_create();
  size_t i = 1;
  options_long_get(argc, argv, &opts, &i);
  options_short_get(argc, argv, &opts, &i);
  options_files_get(argc, argv, &opts, &i);
  return opts;
}
