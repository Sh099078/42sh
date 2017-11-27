#ifndef LEXOR_H
#define LEXOR_H

/*
** Reads the command input looking for the next token according to
** the SCL 2.3. The size_t *index indicates the first character
** that hasn't been used yet by get_next_token from the input.
** RETURN VALUE: An allocated char* containing the copy of the next
** token found in the input.
*/
char *get_next_token(const char *command, size_t *index);

#endif /* LEXHOR_H */
