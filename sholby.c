#include "holberton.h"

int main(int argc, char **argv, char **env)
{
	int res, cpid, chstat = 0;
	char *p = malloc(sizeof(char) * 2);

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
			cmdcall(argv, env);
		}
		else
		{
			wait(&chstat);
			res = isatty(STDIN_FILENO);
			if (!(res))
				return (0);
		}
	}
	return (0);
}

int cmdcall(char **argv, char **env)
{
	size_t buffsize = 1;
	int i = 0, cenv = 0, res;
	const char *s = " ", *t = ":";
	char **sargs, *senv, *spath, *cat, *buff = malloc(sizeof(char) * buffsize);

	if (buff == NULL)
		return (1);
	printf("$ ");
	res = getline(&buff, &buffsize, stdin);
	if (res == -1)
		exit(2);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	buff[i] = '\0';
	sargs = malloc(sizeof(char *) * 100);
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
		printf("%s: 1: %s does not exist\n", argv[0], sargs[0]);
	free(buff);
	free(sargs);
	return (res);
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

