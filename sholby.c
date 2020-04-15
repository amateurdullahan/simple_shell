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
	int err = 0, line = 0, res, stat;
	char *cmd, **sargs, *buff;

	while (argc)
	{
		line++;
		buff = prepbuff();
		if (buff == NULL)
			break;
		else if (buff[0] == '\0')
			continue;
		else if (!(_strcmp(buff, "exit")) && _strlen(buff) > 3)
			exitbltin(buff);
		else if (!(_strcmp(buff, "env")) && _strlen(buff) > 2)
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
		cmd = cmdcall(argv, env, sargs, line);
		if (cmd != NULL)
		{
			res = chexe(cmd, sargs, env);
			wait(&stat);
			free(cmd);
			if (WEXITSTATUS(stat) == -1)
				err = 126;
			else
				err = res;
		}
		else
			err = 127;
		free(sargs), free(buff);
	}
	return (err);
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
		_printf(STDOUT_FILENO, "$ ");
	res = getline(&buff, &buffsize, stdin);
	if (res == -1)
	{
		free(buff);
		if (isatty(STDIN_FILENO))
			_printf(STDOUT_FILENO, "\n");
		return (NULL);
	}
	for (i = 0; buff[i] != '\n' && buff[i] != '\0'; i++)
		;
	buff[i] = '\0';
	buff = trimbuff(buff);
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
	int cpid, res = 0;

	cpid = fork();
	if (cpid == -1)
	{
		_printf(STDERR_FILENO, "Fork failed");
		res = 1;
	}
	else if (cpid == 0)
	{
		res = execve(cmd, sargs, env);
		exit(res);
	}

	return (res);
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
 * @sargs: dbl pointer containing tokenized shell arguments
 * @line: line number
 *
 * Return: concatenated pointer containing working command
 */

char *cmdcall(char **argv, char **env, char **sargs, int line)
{
	struct stat ststr;
	int cenv = 0, res = -1;
	const char *t = ":";
	char *senv, *spath, *cat;

	while (_strncmp(env[cenv], "PATH", 4))
		cenv++;
	senv = malloc(sizeof(char) * (_strlen(env[cenv] + 5) + 1));
	if (senv == NULL)
		return (NULL);
	_strcpy(senv, (env[cenv] + 5));
	if (senv[0] == ':')
		spath = "";
	else
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
		if (spath[0] != '\0')
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
		cat = afterpath(sargs, argv, line);
	}
	free(senv);
	return (cat);
}
