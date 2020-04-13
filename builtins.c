#include "holberton.h"

/**
 * exitbltin - builtin function to exit shell
 * @buff: line containing exit command
 *
 * Return: void
 */

void exitbltin(char *buff)
{
	free(buff);
	exit(0);
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
		printf("%s\n", env[i]);

	free(buff);
}
