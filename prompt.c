#include "shell.h"

/**
 * print_prompt - writes the shell prompt
 * when in interactive mode
 */
void print_prompt(void)
{
	const char *prompt = "$ ";
	
	write(STDOUT_FILENO, prompt, strlen(prompt));
}
