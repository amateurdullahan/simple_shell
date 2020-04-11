#include "holberton.h"

void exitbltin(char *buff)
{
	free(buff);
	exit(0);
}

void envbltin(char *buff, char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);

	free(buff);
}
