#include "options.h"

struct options options_get(int argc, char *argv[])
{
  struct options opts;
  options_long_get(&argc, argv, opts);
  options_short_get(&argc, argv, opts);
  options_files_get(&argc, argv, opts);
  return opts;
}
