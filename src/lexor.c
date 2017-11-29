#include <stdlib.h>

#include "lexor.h"

/*static void update_index(const char *command, size_t *index)
{
  if (!command || strlen(command) < *index)
    return NULL;
  size_t beginning = *index;
  for (; command[(*index)]; (*index)++)
  {
    // token recognition
    continue;
  }
}

char *get_next_token(const char *command, size_t *index)
{
  size_t beginning = *index;
  update_index(command, index);
  if (beginning == *index)
    return NULL;
  char *token = malloc(sizeof(char) * (*index - beginning) + 1);
  if (!token)
    return NULL;
  token[*index -beginning] = 0; //null terminating byte.
  strncpy(token, command + beginning, *index - beginning);
  return token;
}*/
