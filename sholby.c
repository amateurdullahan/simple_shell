#include "holberton.h"

int main(int argc, char **argv, char **env)
{
  int i = 0, res, cpid, cenv = 0;
	size_t buffsize = 1;
	char *buff, **sargs, *senv, *spath, *cat;
	const char *s = " ", *t = ":";

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
			sargs = malloc(100);
			sargs[0] = strtok(buff, s);
			for (i = 0; sargs[i] != NULL; i++)
				sargs[i + 1] = strtok(NULL, s);
			while (strncmp(env[cenv], "PATH", 4))
			  cenv++;
			senv = malloc(sizeof(char) * (strlen(env[cenv] + 5) + 1));
			strcpy(senv, (env[cenv] + 5));
			spath = strtok(senv, t);
			while (spath != NULL)
			  {
			    cat = malloc(sizeof(char) * (strlen(spath) + 2));
			    strcpy(cat, spath); 
			    strcat(cat, "/");
			    strcat(cat, sargs[0]);
			    res = execve(cat, sargs, env);
			    if (res != -1)
			      break;
			    spath = strtok(NULL, t);
			  }
			if (res == -1)
			  printf("%s: 1: %s does not exist\n", argv[0], cat);
			free(buff);
			free(sargs);
			break;
		}
		else
		{
			wait(NULL);
			res = 0;
			res = isatty(res);
			if (res != 1)
			  {
			    return (0);
			  }
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

