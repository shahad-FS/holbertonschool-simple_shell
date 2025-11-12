#include "shell.h"
#include <signal.h>

/**
 * handel_sigint - custom handeler for Ctrl + C (SIGINT)
 * @sig: signal number (unused)
 *
 * Discrption: When user presses Ctrl + C,
 * this function just prints a new prompt line "$ "
 * instead of exeting the shell
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
