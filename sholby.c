#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

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
			for (cenv = 0; env[cenv][0] != 'P' || env[cenv][1] != 'A' || env[cenv][2] != 'T' || env[cenv][3] != 'H'; cenv++)
			  ;
			senv = malloc(sizeof(char) * (strlen(env[cenv] + 5) + 1));
			strcpy(senv, (env[cenv] + 5));
			spath = strtok(senv, t);
			while (spath != NULL)
			  {
			    /*printf("\n%s + %s\n", spath, sargs[0]);*/
			    cat = malloc(sizeof(char) * (strlen(spath) + 2));
			    strcpy(cat, spath); 
			    strcat(cat, "/");
			    /* printf("\nstrcpy %s\n spath %s\n", cat, spath);*/
			    strcat(cat, sargs[0]);
			    /*printf("\nin the while \n%s\n", cat);*/
			    res = execve(cat, sargs, env);
			    if (res != -1)
			      break;
			    /*printf("\nspath %s\n", spath);*/
			    spath = strtok(NULL, t);
			    /*printf("\n%s\n", spath);*/
			  }
			/*printf("\n%s\n", spath);*/
			res = execve(cat, sargs, env);
			if (res == -1)
				printf("%s: 1: %s does not exist\n", argv[0], cat);
			free(buff);
			free(sargs);

			break;
		}
		else
		{
			wait(NULL);
			/*if (isatty(res) != 1)
			  return (0);*/
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

