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
	char *orig, *line;
	int interactive = isatty(STDIN_FILENO);
	int status = 0;

	(void)argc;

	signal(SIGINT, handle_sigint);
	
	    if (argc == 2)
    {
        process_file(argv[1], argv[0]);
        return (status);
    }
	while (1)
	{
		if (interactive)
			print_prompt();

		orig = read_line();
		if (orig == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		line = trim_space(orig);
		if (line[0] != '\0')
		{
			if (_strcmp(line, "exit") == 0)
			{
				free(orig);
				break;
			}
			status = execute_command(line, argv[0]);
		}
		free(orig);
	}
	return (status);
}
