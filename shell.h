#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/* Core functions */
char *_getenv(const char *name);
int parse_arguments(char *line, char **argv);
int execute_command(char *line, char *progname);

/* Helpers */
int try_direct_command(char **argv, char *progname);
int try_path_command(char **argv, char *progname);

/* Other functions used in main */
void print_prompt(void);
char *read_line(void);
char *trim_space(char *str);

#endif /* SHELL_H */
