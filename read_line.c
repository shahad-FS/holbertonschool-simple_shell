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

	read = _getline(&line, &len);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (read > 0 && line[read - 1] == '\n')
		line[read - 1] = '\0';

	return (line);
}
