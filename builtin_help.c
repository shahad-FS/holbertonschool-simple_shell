#include "shell.h"

/**
 * _help - help commande
 * @av: arguments valeur
 *
 * Return: 0
 */

int _help(char **av)
{
	if (av[2])
		write(2, "too many arguments\n", 20);
	if (av[1] == NULL)
		write(2, "Too few arguments\n", 19);
	else
	{
		if (_strcmp("cd", av[1]) == 0)
		{
			write(1, "cd command is used for change the shell working ", 49);
			write(1, "directory.\n", 12);
		}
		else if (_strcmp("exit", av[1]) == 0)
			write(1, "exit command is used for exit the shell.\n", 42);
		else if (_strcmp("echo", av[1]) == 0)
		{
			write(1, "echo command is used for write arguments to the standar ", 57);
			write(1, "output.\n", 9);
		}
		else if (_strcmp("help", av[1]) == 0)
		{
			write(1, "help command is used for display information about builtin.", 60);
			write(1, "commands.\n", 11);
		}
		else if (_strcmp("alias", av[1]) == 0)
		{
			write(1, "alias command is used for define or display aliases ", 53);
			write(1, "commands.\n", 11);
		}
		else
			write(2, "Command not found\n", 19);
	}
	return (0);
}
