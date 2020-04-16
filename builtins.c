#include "holberton.h"

/**
 * exitbltin - builtin function to exit shell
 * @buff: line containing exit command
 *
 * Return: void
 */

void exitbltin(char *buff)
{
  int i, e;
  const char *c = " ";
  char **exitcode;
  exitcode = malloc(sizeof(char *) * 100);
  exitcode[0] = strtok(buff, c);
  for (i = 0; i < 1; i++)
    exitcode[i + 1] = strtok(NULL, c);

  e = _atoi(exitcode[i]);
  free(exitcode);
  free(buff);
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
