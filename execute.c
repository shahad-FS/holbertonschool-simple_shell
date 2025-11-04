#include "shell.h"

/**
 * execute_command - exec input command
 * @line: line contians the command
 *
 * Return: void
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	line[strcspn(line, "\n")] = '\0';
	
	if (line[0] == '\0')
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		(void)status;
	}
}
