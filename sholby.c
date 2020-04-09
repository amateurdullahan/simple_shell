#include "holberton.h"

int main(int argc, char **argv, char **env)
{
	int i = 0, res, cpid = -1;
	size_t buffsize = 1;
	char *cmd, **sargs, *buff = malloc(sizeof(char) * buffsize);

	while (1)
	{
		if (buff == NULL)
			return (1);
		printf("$ ");
		res = getline(&buff, &buffsize, stdin);
		if (res == -1)
		{
			printf("\n");
			return (1);
		}
		if (!(_strncmp(buff, "exit", 4)))
			return (0);
		while (buff[i] != '\n' && buff[i] != '\0')
			i++;
		buff[i] = '\0';

		sargs = getsargs(buff);

		cmd = cmdcall(argv, env, buff, sargs);

		chexe(cmd, sargs, env);

		wait(NULL);
		if (!(isatty(STDIN_FILENO)))
			return (0);
	}
	return (0);
}

void chexe(char *cmd, char **sargs, char **env)
{
	int cpid;

	cpid = fork();
	if (cpid == -1)
	{
		printf("Fork failed");
		return;
	}
	else if (cpid == 0)
	{
		execve(cmd, sargs, env);
		return;
	}
}

char **getsargs(char *buff)
{
	int i;
	char **sargs;
	const char *s = " ";

	sargs = malloc(sizeof(char *) * 100);
	sargs[0] = strtok(buff, s);
	for (i = 0; sargs[i] != NULL; i++)
		sargs[i + 1] = strtok(NULL, s);
	return (sargs);
}

char *cmdcall(char **argv, char **env, char *buff, char **sargs)
{
	struct stat *ststr = malloc(sizeof(struct stat *));
	int cenv = 0, res;
	const char *t = ":";
	char *senv, *spath, *cat;

	while (_strncmp(env[cenv], "PATH", 4))
		cenv++;
	senv = malloc(sizeof(char) * (_strlen(env[cenv] + 5) + 1));
	_strcpy(senv, (env[cenv] + 5));
	spath = strtok(senv, t);
	while (spath != NULL)
	{
		cat = malloc(sizeof(char) * (_strlen(spath) + 2));
		_strcpy(cat, spath);
		_strcat(cat, "/");
		_strcat(cat, sargs[0]);
		res = stat(cat, ststr);
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
	free(buff);
	free(ststr);
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

