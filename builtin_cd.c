#include "shell.h"

/*
 * builtin_cd - handles the builtin cd command
 * @argv: array of arguments, e.g. {"cd", "dir", NULL}
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_cd(char **argv)
{
	char *dir = argv[1];
	char cwd[1024];
	char *oldpwd = getcwd(NULL, 0);

	if (!oldpwd)
	{
		perror("getcwd");
		return (1);
	}

	if (dir == NULL)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			dir = "/";
		}
	}

	else if (_strcmp(dir, "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (!dir)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(oldpwd);
			return (1);
		}
		printf("%s\n", dir);
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}

	setenv("OLDPWD", oldpwd, 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	free(oldpwd);
	return (0);
}
