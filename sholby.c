#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv, char **env)
{
	int i = 0, res, cpid;
	size_t buffsize = 1;
	char *buff;

	while (1)
	{
		cpid = fork();
		if (cpid == -1)
		{
			printf("Fork failed");
			return (1);
		}
		else if (cpid == 0)
		{
			buff = malloc(sizeof(char) * buffsize);
			if (buff == NULL)
			{
				printf("Failed to malloc.\n");
				return (1);
			}
			printf("$ ");
			getline(&buff, &buffsize, stdin);
			while (buff[i] != '\n' && buff[i] != '\0')
				i++;
			buff[i] = '\0';
			res = execve(buff, argv, env);
			if (res == -1)
				printf("%s: 1: %s does not exist\n", argv[0], buff);
			free(buff);
			break;
		}
		else
		{
			wait(NULL);
			if (isatty(res) != 1)
			  return (0);
		}
	}
	return (0);
}
