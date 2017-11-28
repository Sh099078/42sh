#include "options.h"

static struct options options_create(void)
{
  struct options opts;
  opts.shopt_vars = 0;
  opts.norc = 0;
  opts.version = 0;
  return opts;
}

static int is_long_option(const char *opt)
{
  return strlen(opt) > 2 && !strncmp(opt, "--", 2);
}

static int is_beginning(const char *s, const char *opt)
{
  if (strlen(s) > strlen(opt))
    return 0;
  if (strcmp(s, opt))
    warnx("%s: invalid option, but interpreted as %s", s, opt);
  return 1;
}

static void options_long_get(size_t argc,char **argv,
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

static void options_short_get(size_t argc,char **argv,
                             struct options *opts, size_t *i)
{
  return;
}

static void options_files_get(size_t argc,char **argv,
                             struct options *opts, size_t *i)
{
  return;
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
