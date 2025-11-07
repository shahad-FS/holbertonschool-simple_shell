#include "shell.h"
#include <sys/stat.h>

/**
 * parse_arguments - tokenize command line into argv array
 * @line: input command line
 * @argv: array to store arguments
 *
 * Return: number of arguments
 */
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

/**
 * execute_command - fork and execute a command
 * @line: command line
 * @progname: shell program name (for error messages)
 *
 * Return: 0 on success, 1 on error, 127 if command not found
 */
int execute_command(char *line, char *progname)
{
	pid_t pid;
	int status;
	char *argv[64];
	int argc;
	char *path_env, *path_copy, *dir, full_path[256];
	struct stat st;
	int found = 0;

	if (!line || !*line)
		return (0);

	argc = parse_arguments(line, argv);
	if (argc == 0)
		return (0);

	/* Handle commands with / or ./ */
	if (argv[0][0] == '/' || argv[0][0] == '.')
	{
		if (access(argv[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
			return (127);
		}
		found = 1;
	}
	else
	{
		/* Search command in PATH */
		path_env = getenv("PATH");
		if (!path_env || !*path_env)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
			return (127);
		}

		path_copy = strdup(path_env);
		if (!path_copy)
			return (1);

		dir = strtok(path_copy, ":");
		while (dir)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
			if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			{
				found = 1;
				break;
			}
			dir = strtok(NULL, ":");
		}
		free(path_copy);

		if (!found)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
			return (127);
		}
	}

	/* Fork only if command exists */
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
			execve(full_path, argv, environ);

		perror(progname);
		_exit(127);
	}
	else
		wait(&status);

	return (0);
}
