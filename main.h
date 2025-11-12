#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>

/* Custom getline function */
ssize_t _getline(char **lineptr);

/* Custom tokenizer function */
char **tokenize_input(char *line);

#endif /* MAIN_H */
