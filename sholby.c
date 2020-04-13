#include "holberton.h"

/**
 * main - run basic loop of shell
 * @argc: arguemnt count
 * @argv: dbl pointer of arguments
 * @env: dbl pointer of enviroment variables
 *
 * Return: 0 if successful OR 1 if failure
 */

int main(int argc, char **argv, char **env)
{
	int i, res, cpid = -1;
	char *cmd, **sargs, *buff;

	while (1)
	{
		buff = prepbuff();
		if (!(_strcmp(buff, "exit")))
			exitbltin(buff);
		else if (!(_strcmp(buff, "env")))
		{
			envbltin(buff, env);
			continue;
		}
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

/**
 * prepbuff - prep the buff for shell
 *
 * Return: buff that is prepped for shell
 */

char *prepbuff()
{
	int i, res;
	size_t buffsize = 1024;
	char *buff = malloc(sizeof(char) * buffsize);

	if (buff == NULL)
		exit(1);
	if (isatty(STDIN_FILENO))
		printf("$ ");
	res = getline(&buff, &buffsize, stdin);
	if (res == -1)
	{
		free(buff);
		printf("\n");
		exit(1);
	}
	for (i = 0; buff[i] != '\n' && buff[i] != '\0'; i++)
		;
	buff[i] = '\0';

	return (buff);
}

/**
 * chexe - fork the child and execute the command
 * @cmd: command to be executed
 * @sargs: dbl pointer containing arguments for command
 * @env: dbl pointer containing enviromental variables
 *
 * Return: 0 if successful OR -1 if failure
 */

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

/**
 * getsargs - get shell arguments
 * @buff: pointer containing arguments to be parsed
 *
 * Return: dbl pointer containing tokenized arguments
 */

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

/**
 * cmdcall - get command to be executed
 * @argv: dbl pointer containing array of arguments
 * @env: dbl pointer containing enviromental variables
 * @buff: pointer containing buff of stdin
 * @sargs: dbl pointer containing tokenized shell arguments
 *
 * Return: concatenated pointer containing working command and arguements
 */

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
		cat = malloc(sizeof(char) * 1024);
		if (!(strncmp(sargs[0], "./", 2)))
		{
			getcwd(cat, 1024);
			_strcat(cat, argv[0] + 1);
		}
		/*else if (!(strncmp(sargs[0], "../", 3))
		*/res = stat(cat, &ststr);
		if (res == -1)
		{
			printf("%s: 1: %s does not exist\n", argv[0], sargs[0]);
			cat = NULL;
		}
	}
	free(senv);
	return (cat);
}
