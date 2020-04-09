#include "holberton.h"

int main(int argc, char **argv, char **env)
{
	int i, res, cpid = -1;
	size_t buffsize;
	char *cmd, **sargs, *buff;

	while (1)
	{
		buffsize = 1024;
		buff = malloc(sizeof(char) * buffsize);
		if (buff == NULL)
			return (1);
		if (isatty(STDIN_FILENO))
			printf("$ ");
		res = getline(&buff, &buffsize, stdin);
		if (res == -1)
		{
			free(buff);
			printf("\n");
			return (1);
		}
		if (!(_strncmp(buff, "exit", 4)))
		{
			free(buff);
			return (0);
		}
		for (i = 0; buff[i] != '\n' && buff[i] != '\0'; i++)
			;
		buff[i] = '\0';

		sargs = getsargs(buff);
		if (sargs == NULL)
		{
			free(buff);
			return (1);
		}
		cmd = cmdcall(argv, env, buff, sargs);
		if (cmd != NULL)
		{
			chexe(cmd, sargs, env);
			wait(NULL);
			free(cmd);
		}

		free(sargs);
		free(buff);
		if (!(isatty(STDIN_FILENO)))
			return (0);
	}
	return (0);
}

int chexe(char *cmd, char **sargs, char **env)
{
	int cpid;

	cpid = fork();
	if (cpid == -1)
	{
		printf("Fork failed");
		return (-1);
	}
	else if (cpid == 0)
	{
		execve(cmd, sargs, env);
		return (0);
	}
}

char **getsargs(char *buff)
{
	int i;
	char **sargs;
	const char *s = " ";

	sargs = malloc(sizeof(char *) * 100);
	if (sargs == NULL)
		return (NULL);
	sargs[0] = strtok(buff, s);
	for (i = 0; sargs[i] != NULL; i++)
		sargs[i + 1] = strtok(NULL, s);
	return (sargs);
}

char *cmdcall(char **argv, char **env, char *buff, char **sargs)
{
	struct stat ststr;
	int cenv = 0, res;
	const char *t = ":";
	char *senv, *spath, *cat;

	while (_strncmp(env[cenv], "PATH", 4))
		cenv++;
	senv = malloc(sizeof(char) * (_strlen(env[cenv] + 5) + 1));
	if (senv == NULL)
		return (NULL);
	_strcpy(senv, (env[cenv] + 5));
	spath = strtok(senv, t);
	while (spath != NULL)
	{
		cat = malloc(sizeof(char) * (_strlen(spath) + _strlen(sargs[0]) + 2));
		if (cat == NULL)
		{
			free(senv);
			return (NULL);
		}
		_strcpy(cat, spath);
		_strcat(cat, "/");
		_strcat(cat, sargs[0]);
		res = stat(cat, &ststr);
		if (res == 0)
			break;
		spath = strtok(NULL, t);
		free(cat);
	}
	if (res == -1)
	{
		printf("%s: 1: %s does not exist\n", argv[0], sargs[0]);
		cat = NULL;
	}
	free(senv);
	return (cat);
}

char **tokenize(char *buff)
{
	int i, j, k, l = 0, m = 0, tkount = 0;
	char **tokens;

	for (i = 0; buff[i]; i++)
	{
		if (buff[i] == ' ' || buff[i] == '\0')
			tkount++;
	}
	tokens = malloc(sizeof(char *) * (tkount + 1));

	for (i = 0; i < tkount; i++)
	{
		k = 0;
		while (buff[k + l] != ' ' && buff[k + l] != '\0')
		k++;
		l += k;
		if (buff[l] != '\0')
			l++;
		tokens[i] = malloc(sizeof(char) * (k + 1));
		for (j = 0; buff[m] != ' ' && buff[m] != '\0'; j++, m++)
			tokens[i][j] == buff[m];
		if (buff[m] != '\0')
			m++;
		tokens[i][j] == '\0';
	}
	tokens[i] = NULL;
	return (tokens);
}

