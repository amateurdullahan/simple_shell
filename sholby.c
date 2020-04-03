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
	char *sargs;
	const char s = '-';

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
			sargs = strtok(buff, s);
			res = execve(sargs, argv, env);
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


char **tokenize(char *buff)
{
  int i, j, k, l = 0, m = 0, tkount = 0;
  char **tokens;

  for (i = 0; buff[i]; i++)
    {
      if (buff[i] == ' ' || buff[i] == '\0')
	{
	  tkount++;
	}
    }
  tokens = malloc(sizeof(char *) * (tkount + 1));

  for (i = 0; i < tkount; i++)
    {
      k = 0;
      while (buff[k+l] != ' ' && buff[k+l] != '\0')
	{
	  k++;
	}
      l += k;
      if (buff[l] != '\0')
	l++;
      tokens[i] = malloc(sizeof(char) * (k + 1));
      for (j = 0; buff[m] != ' ' && buff[m] != '\0'; j++, m++)
	{
	  tokens[i][j] == buff[m];
	}
      if (buff[m] != '\0')
	m++;
      tokens[i][j] == '\0';
    }
  tokens[i] = NULL;
  return (tokens);
}
