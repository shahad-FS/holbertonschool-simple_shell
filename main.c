#include "shell.h"

/**
 * main - entry point for simple shell 0.1
 * @argc:  argument count (unused)
 * @argv: argument vector (argv[0] used for error massage)
 *
 * Return: always 0
 */
int main(void)
{
	char *line;

	while (1)
	{
		print_prompt();
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		execute_command(line);
		free(line);
	}
	return (0);
}
