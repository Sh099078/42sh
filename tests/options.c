#include "../src/options.h"
#include <stdio.h>

static void options_print(struct options options)
{
  printf("{\n\tshopt_var: %d\n\tnorc: %d\n\tversion: %d\n}\n",
         options.shopt_vars, options.norc, options.version);
}

int main(int argc, char **argv)
{
  struct options options = options_get(argc, argv);
  options_print(options);
  return 0;
}
