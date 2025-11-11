#include "shell.h"

/**
 * _getenv - custom getenv implementation using environ
 * @name: name of the environment variable
 * Return: pointer to its value or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

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
 * execute_command - main execution logic (delegates to helpers)
 * @line: input line
 * @progname: shell name
 * Return: 0 on success, 127 if not found
 */
int execute_command(char *line, char *progname)
{
	char *argv[64];
	int argc;
	char *path_env;
	int status = 0;

	if (!line || !*line)
		return (0);

	argc = parse_arguments(line, argv);
	if (argc == 0)
		return (0);

	if (argv[0][0] == '/' || argv[0][0] == '.')
		return (try_direct_command(argv, progname));
	
	path_env = _getenv("PATH");

	if (path_env == NULL || *path_env == '\0')
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, argv[0]);
		return (127);
	}
	status = try_path_command(argv, progname);
	return (status);
}
