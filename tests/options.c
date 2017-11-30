#include "../src/options.h"
#include <stdio.h>

static void options_print(struct options options)
{
  printf("{\n\tshopt_var: %d\n\t-c: %d\n\tnorc: %d\n\tversion: %d\n",
         options.shopt_vars, options.c, options.norc, options.version);
  if (options.files)
  {
    printf("\tfiles: [");
    for (size_t i = 0; i < options.files_len; i++)
      printf("%s ;", options.files[i]);
    printf("]\n");
  }
  printf("\tfiles_len: %zu\n}\n", options.files_len);
}

int main(int argc, char **argv)
{
  struct options options = options_get(argc, argv);
  options_print(options);
  return 0;
}
