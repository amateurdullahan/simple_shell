#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	int res = 0;
	size_t buffsize = 1;
	char *buff = malloc(sizeof(char) * buffsize);

	if (buff == NULL)
	{
		printf("Failed to malloc.\n");
		return (1);
	}

	printf("$ ");

	getline(&buff, &buffsize, stdin);

	buff[buffsize - 2] = '\0';

	res = execve(buff, argv, env);

	if (res == -1)
		printf("%s: 1: %s does not exist\n", argv[0], buff);

	return (0);
}
