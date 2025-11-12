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
	FILE *fp_file = NULL;
	char *file_line = NULL;
	size_t file_len = 0;
	ssize_t file_read_len;

	(void)argc;

	signal(SIGINT, handle_sigint);
	
	if (argc > 1)
    	{
        	fp_file = fopen(argv[1], "r");
        	if (!fp_file)
        	{
        	    	perror("fopen");
            		return (1);
        	}

        	while ((file_read_len = getline(&file_line, &file_len, fp_file)) != -1)
        	{
            	line = trim_space(file_line);
            	if (line[0] != '\0')
                	status = execute_command(line, argv[0]);
        	}

        	free(file_line);
        	fclose(fp_file);
        	return status;
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
