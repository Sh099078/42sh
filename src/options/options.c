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
  opts->c = 1;
  // Have to clarify stuff about positional parameters first
  argc = argc;
  argv = argv;
  i = i;
}

static void shopt_var_set(struct options *opts, int set, int shopt_var)
{
  if (set)
    opts->shopt_vars |= shopt_var;
  else
    opts->shopt_vars -= shopt_var;
}

static int shopt_handle_option(const char *opt, int set,
                                struct options *opts)
{
  char *shopt_options[] = { "ast_print", "dotglob", "expand_aliases",
                            "extglob", "nocaseglob", "nullglob", "sourcepath",
                            "xpg_echo", 0 };
  if (!strcmp(shopt_options[0], opt))
shopt_var_set(opts, set, AST_PRINT);
  else if (!strcmp(shopt_options[1], opt))
shopt_var_set(opts, set, DOTGLOB);
  else if (!strcmp(shopt_options[2], opt))
shopt_var_set(opts, set, EXPAND_ALIASES);
  else if (!strcmp(shopt_options[3], opt))
shopt_var_set(opts, set, EXTGLOB);
  else if (!strcmp(shopt_options[4], opt))
shopt_var_set(opts, set, NOCASEGLOB);
  else if (!strcmp(shopt_options[5], opt))
shopt_var_set(opts, set, NULLGLOB);
  else if (!strcmp(shopt_options[6], opt))
shopt_var_set(opts, set, SOURCEPATH);
  else if (!strcmp(shopt_options[7], opt))
shopt_var_set(opts, set, XPG_ECHO);
  else
  {
    fprintf(stdout, "%s: invalid shopt option\n"
            "shopt_options available: ast_print dotglob expand_aliases"
            " extglob nocaseglob nullglob sourcepath xpg_echo\n", opt);
    return 0;
  }
  return 1;
}

static int is_short_option(const char *opt)
{
  return strlen(opt) > 1 && (opt[0] == '-' || opt[0] == '+');
}

/**
 ** @brief Checks if opt was the '--' end of options signal
 */
static int is_end_option(const char *opt)
{
  return !opt[1] && opt[0] == '-';
}

/**
 ** @brief parse [-+]O option, setting shopt variables
 */
static void options_shopt(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  int is_set = argv[(*i)][0] == '-';
  for (; *i + 1 < argc && !is_short_option(argv[*i + 1]); (*i)++)
  {
    if (!shopt_handle_option(argv[*i + 1], is_set, opts))
      break;
  }
}

/**
 ** @brief sub-function of options_get, taking care of short options
 */
static void options_short_get(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  // TODO
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
      options_shopt(argc, argv, opts, i);
    else
      errx(1, "%s: invalid option\n"
              "Usage: 42sh [GNU long options] [options] [file]", opt);
  }
  if (is_c_enabled)
    options_c(argc, argv, opts, i);
}

/**
 ** @brief sub-function of options_get, taking care of files
 */
static void options_files_get(size_t argc, char **argv,
                             struct options *opts, size_t *i)
{
  if (*i  < argc)
  {
    opts->files = argv + *i;
    opts->files_len = argc - *i;
  }
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
