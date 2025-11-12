#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
    char *line = NULL;
    char **args;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        if (_getline(&line) == -1)
        {
            free(line);
            break;
        }

        args = tokenize_input(line);
        if (!args || !args[0])
        {
            free(line);
            free(args);
            continue;
        }

        pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            wait(&status);
        }
        else
        {
            perror("fork");
        }

        free(line);
        for (int i = 0; args[i]; i++)
            free(args[i]);
        free(args);
    }

    return 0;
}
