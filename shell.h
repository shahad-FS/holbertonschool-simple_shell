#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_prompt(void);
char *read_line(void);
char *trim_space(char *str);
int execute_command(char *line, char *progname);

#endif
