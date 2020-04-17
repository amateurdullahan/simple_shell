#include "holberton.h"

/**
 * exitbltin - builtin function to exit shell
 * @buff: line containing exit command
 * @argv: args
 * @line: line number
 * @err: custom errno
 *
 * Return: void
 */

void exitbltin(char *buff, char **argv, int line, int *err)
{
	int i, f;
	char **exitcode;

	exitcode = tokenize(buff, ' ');
	free(buff);
	if (exitcode[1] != NULL)
	{
		for (f = 0; exitcode[1][f]; f++)
		{
			if (exitcode[1][f] < '0' || exitcode[1][f] > '9')
			{
				prerr(argv, exitcode, line, 666);
				for (i = 0; exitcode[i] != NULL; i++)
					free(exitcode[i]);
				free(exitcode);
				if (isatty(STDIN_FILENO))
					return;
				exit(2);
			}
		}
		*err = _atoi(exitcode[1]);
		if (*err > 255)
			*err = *err % 256;
	}
	for (i = 0; exitcode[i] != NULL; i++)
		free(exitcode[i]);
	free(exitcode);
	exit(*err);
}

/**
 * envbltin - print enviromental variables
 * @buff: line containing command
 * @env: dbl pointer containing enviromental variables
 *
 * Return: void
 */

void envbltin(char *buff, char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		_printf(STDOUT_FILENO, "%s\n", env[i]);

	free(buff);
}
