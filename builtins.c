#include "holberton.h"

/**
 * exitbltin - builtin function to exit shell
 * @buff: line containing exit command
 * @argv: args
 * @line: line number
 *
 * Return: void
 */

void exitbltin(char *buff, char **argv, int line)
{
	int i, e = errno, f;
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
				return;
			}
		}
		e = _atoi(exitcode[1]);
		if (e > 255)
			e = e - 256;
	}
	for (i = 0; exitcode[i] != NULL; i++)
		free(exitcode[i]);
	free(exitcode);
	exit(e);
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
