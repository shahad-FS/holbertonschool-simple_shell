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
	char *argv[2];
	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		return (-1);
	}
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(line, argv, environ) == -1)
		{
			perror(progname);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
