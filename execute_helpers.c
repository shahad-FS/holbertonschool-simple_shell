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
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror(progname);
		_exit(127);
	}
	wait(&status);
	return (0);
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
	char full_path[256];
	char path_copy[1024];

	path_env = _getenv("PATH");
	if (!path_env || !*path_env)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
		return (127);
	}

	strncpy(path_copy, path_env, sizeof(path_copy) - 1);
	path_copy[sizeof(path_copy) - 1] = '\0';

	path_token = strtok(path_copy, ":");
	while (path_token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path_token, argv[0]);
		if (access(full_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(full_path, argv, environ);
				perror(progname);
				_exit(127);
			}
			wait(&status);
			return (0);
		}
		path_token = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
	return (127);
}

