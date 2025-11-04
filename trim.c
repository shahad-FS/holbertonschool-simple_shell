#include "shell.h"

/**
 * trim_space - remove leading and trailling space from a string
 * @str: string to trim
 * 
 * Return: pointer to trimmed string
 */
char *trim_space(char *str)
{
	char *end;

	if (str == NULL)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return (str);
}
