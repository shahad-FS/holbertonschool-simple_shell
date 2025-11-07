#include "shell.h"

/**
 * execute_command - fork and executes command
 * @line: command line
 * @progname: name of the shell program for error massages
 *
 * Return: 0 on success, -1 on error
 */
int execute_command(char *line, char *progname)
{
	pid_t pid;
	int status;
	char *argv[64];
	char *token;
	char path[256];
	int i = 0;

	if (!line || !*line)
		return (0);
	token = strtok(line, " \t\n");

	while (token != NULL && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	if (argv[0] == NULL)
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
		{
			execve(argv[0], argv, environ);
		}
		else
		{
			snprintf(path, sizeof(path), "/bin/%s", argv[0]);
			execve(path, argv, environ);
		}
		perror(progname);
		_exit(127);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
