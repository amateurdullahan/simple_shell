#include "holberton.h"

/**
 * exitbltin - builtin function to exit shell
 * @buff: line containing exit command
 *
 * Return: void
 */

void exitbltin(char *buff)
{
  int i, e, f;
  const char *c = " ";
  char **exitcode;
  exitcode = malloc(sizeof(char *) * 100);
  exitcode[0] = strtok(buff, c);
  for (i = 0; i < 1; i++)
    exitcode[i + 1] = strtok(NULL, c);

  for (f = 0; exitcode[i][f]; f++)
    {
      if (exitcode[i][f] < '0' || exitcode[i][f] > '9')
	return;
    }
  e = _atoi(exitcode[i]);
  free(exitcode);
  free(buff);
  if (e > 255)
    e = e - 256;
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
