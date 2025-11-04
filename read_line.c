#include "shell.h"

/**
 * read_line - read user input line
 *
 * Return: the line read, or NULL if the end-of-file (EOF) is reached
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
