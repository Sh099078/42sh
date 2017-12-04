#include <stdlib.h>

#include "lexer.h"

/*static enum token_type update_index(const char *command, size_t *index)
{
  if (!command || strlen(command) < *index)
    return NULL;
  size_t beginning = *index;
  for (; command[(*index)]; (*index)++)
  {
    // token recognition
    continue;
  }
}*/

struct token get_next_token(struct context *context, size_t *index);
{
  /*size_t beginning = *index;
  update_index(command, index);
  if (beginning == *index)
    return NULL;
  char *token_str = malloc(sizeof(char) * (*index - beginning) + 1);
  if (!token_str)
    return NULL;
  token_str[*index - beginning] = 0; //null terminating byte.
  strncpy(token_str, command + beginning, *index - beginning);
  struct token token =
  {
    token_type,
    token_str
  };
  return token;*/
  context = context;
  index = index;
  return NULL;
}
