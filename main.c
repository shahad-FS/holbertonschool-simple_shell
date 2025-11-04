#include "shell.h"

/**
 * main - entry point for simple shell 0.1
 * @argc:  argument count (unused)
 * @argv: argument vector (argv[0] used for error massage)
 *
 * Return: always 0
 */
int main(int argc, char **argv)
{
	char *line;
	int interactive = isatty(STDIN_FILENO);

	(void)argc;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_line();
		if (line == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[0] != '\0')
			execute_command(line, argv[0]);
		free(line);
	}
	return (0);
}
