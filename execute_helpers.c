#include "shell.h"

/**
 * try_direct_command - executes command if it’s a direct path
 * @argv: command and its arguments
 * @progname: shell name
 * Return: 0 on success, 127 on not found
 */
int try_direct_command(char **argv, char *progname)
{
	pid_t pid;
	int status;

	if (access(argv[0], X_OK) != 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	else if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror(progname);
		_exit(127);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 127);
}

/**
 * try_path_command - searches PATH and executes if found
 * @argv: command and its arguments
 * @progname: shell name
 * Return: 0 on success, 127 on not found
 */
int try_path_command(char **argv, char *progname)
{
	pid_t pid;
	int status;
	char *path_env, *path_token;
	char full_path[512];
	char *path_copy;

	path_env = _getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
		return (127);
	}

	path_copy = strdup(path_env);
	if (!path_copy)
		return (127);
	path_token = strtok(path_copy, ":");

	while (path_token)
	{
		sprintf(full_path, "%s/%s", path_token, argv[0]);

		if (access(full_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				free(path_copy);
				return (1);
			}
			else if (pid == 0)
			{
				execve(full_path, argv, environ);
				perror(progname);
				free(path_copy);
				_exit(127);
			}
			waitpid(pid, &status, 0);
			free(path_copy);
			return (WIFEXITED(status) ? WEXITSTATUS(status) : 127);
		}

		path_token = strtok(path_copy, ":");
	}

	fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
	free(path_copy);
	return (127);
}
