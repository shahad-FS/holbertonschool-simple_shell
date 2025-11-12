#include "shell.h"

/**
 * _setenv - set or modifies an environment variable
 * @var: name of the variable
 * @value: value of the variable
 * 
 * Return: 0 on successs, -1 on failure
 */
int _setenv(const char *var, const char *value)
{
	int i;
	size_t len;
	char *new_var;
	char **new_environ;
	if (!var || !value)
	{
		return (-1);
	}
	len = strlen(var);
	new_var = malloc(len + strlen(value) + 2);

	if (!new_var)
	{
		return (-1);
	}

	snprintf(new_var, len + strlen(value) + 2, "%s=%s", var, value);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			environ[i] = new_var;
			return (0);
		}
	}
	
	new_environ = realloc(environ, sizeof(char *) * (i + 2));
	
	if (!new_environ)
	{
		free(new_var);
		return (-1);
	}
	environ = new_environ;
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - removes an environment variable
 * @var; name of the variable
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *var)
{
	int i, j;
	size_t len;

	if (!var)
	{
		return (-1);
	}

	len = strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);

			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
	}
	return (0);
}

/**
 * builtin_setenv - builtin handler for setenv command
 * @args: array of arguments
 *
 * Return: 0 on success
 */
int builtin_setenv(char **args)
{
	if (!args[1] || !args[2])
	{
		write(2, "Usage: setenv VARIABLE VALUE\n", 29);
		return (1);
	}

	if (_setenv(args[1], args[2]) == -1)
	{
		write(2, "setenv: faild\n", 15);
		return (1);
	}
	return (0);
}

/**
 * builtin_unsetenv - builtin handler for unsetenv command
 * @args: array of arguments
 *
 * Return: 0 on success
 */
int builtin_unsetenv(char **args)
{
	if (!args[1])
	{
		write(2, "Usage: unsetenv VARIABLE\n", 25);
		return (1);
	}
	if (_unsetenv(args[1]) == -1)
	{
		write(2, "unsetenv: failed\n", 17);
		return (1);
	}
	return (0);
}
