#include "shell.h"

int parse_arguments(char *line, char **argv)
{
    char *token;
    int i = 0;

    token = strtok(line, " \t\n");
    while (token != NULL && i < 63)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[i] = NULL;

    return (i);
}

int execute_command(char *line, char *progname)
{
    pid_t pid;
    int status;
    char *argv[64];
    char path[256];
    int argc;

    if (!line || !*line)
        return (0);

    argc = parse_arguments(line, argv);
    if (argc == 0)
        return (0);

    pid = fork();
    if (pid == -1)
    {
        perror(progname);
        return (1);
    }
    if (pid == 0)
    {
        if (argv[0][0] == '/' || argv[0][0] == '.')
            execve(argv[0], argv, environ);
        else
        {
            snprintf(path, sizeof(path), "/bin/%s", argv[0]);
            execve(path, argv, environ);
        }
        perror(progname);
        _exit(127);
    }
    else
        wait(&status);

    return (0);
}
