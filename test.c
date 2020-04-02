#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	size_t buffsize = 100;
	char *buff = malloc(sizeof(char) * buffsize);

	if (buff == NULL)
	{
		printf("Failed to malloc.\n");
		return (1);
	}

	printf("$ ");

	getline(&buff, &buffsize, stdin);

	execve(buff, argv, env);

	return (0);
}
