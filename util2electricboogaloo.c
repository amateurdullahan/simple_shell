#include "holberton.h"

/**
 * tokenize - parse buff into tokens
 * @buff: pointer to be tokenized
 * @delim: delimiter to split at
 *
 * Return: pointer to array of tokens
 */

char **tokenize(char *buff, char delim)
{
	int i, k, j, d, len = _strlen(buff);
	char **toks = malloc(sizeof(char *) * 1024);

	for (i = 0, k = 0, j = 0; i <= len; i++)
	{
		if (buff[i] == delim || buff[i] == '\0')
		{
			toks[k] = malloc(sizeof(char) * (i - j + 1));
			for (d = 0; j + d < i; d++)
				toks[k][d] = buff[j + d];
			toks[k][d] = '\0';
			j = i + 1;
			k++;
		}
	}
	toks[k] = NULL;
	return (toks);
}

/**
 * pthexp - expands a relative path to an absolute path
 * @rel: relative path to expand
 * @dest: buffer to save absolute path to
 */
void pthexp(char *rel, char *dest)
{
	char *curr, *next;
	char *tmp = malloc(sizeof(char) * 1024);

	if (!(_strncmp(rel, "./", 2)))
	{
		getcwd(dest, 1024);
		_strcat(dest, rel + 1);
	}
	else if (!(_strncmp(rel, "../", 2)))
	{
		curr = strtok(getcwd(tmp, 1024), "/");
		next = strtok(NULL, "/");
		if (curr != NULL)
		{
			_strcpy(dest, "/");
			_strcat(dest, curr);
		}
		while (next != NULL)
		{
			curr = next;
			next = strtok(NULL, "/");
			if (next != NULL)
			{
				_strcat(dest, "/");
				_strcat(dest, curr);
			}
		}
		_strcat(dest, rel + 2);
	}
	free(tmp);
}

/**
 * trimbuff - trims the spaces from the beginning and end of buff
 * @buff: buff to trim
 *
 * Return: pointer to realloced buff with trimmed result
 */
char *trimbuff(char *buff)
{
	int i, c1, c2 = 0, l = _strlen(buff);
	char *newbuff;

	for (c1 = 0; buff[c1] == ' '; c1++)
		;
	for (i = l - 1; buff[i] == ' '; i--, c2++)
		;
	buff[i + 1] = '\0';

	newbuff = malloc(sizeof(char) * (l - (c1 + c2) + 1));

	_strcpy(newbuff, buff + c1);
	free(buff);
	return (newbuff);
}

/**
 * afterpath - checks non-path files
 * @sargs: shell args
 * @argv: args
 * @line: line count
 *
 * Return: pointer to new path
 */
char *afterpath(char **sargs, char **argv, int line)
{
	struct stat ststr;
	char *cat;
	int res;

	cat = malloc(sizeof(char) * 1024);
	cat[0] = '\0';
	if (!(_strncmp(sargs[0], "./", 2)) || !(_strncmp(sargs[0], "../", 3)))
		pthexp(sargs[0], cat);
	else if (!(_strncmp(sargs[0], "/", 1)))
		_strcpy(cat, sargs[0]);
	res = stat(cat, &ststr);
	if (res == -1)
	{
		prerr(argv, sargs, line, 127);
		free(cat);
		cat = NULL;
	}

	return (cat);
}

/**
 * prerr - prints error messages
 * @argv: prog args
 * @line: line number
 * @sargs: command args
 * @err: error number
 */
void prerr(char **argv, char **sargs, int line, int err)
{
	char *num = malloc(1024);
	char *str;

	_itoa(line, num, 10);
	str = malloc(sizeof(char) *
		(_strlen(argv[0]) + _strlen(num) + _strlen(sargs[0]) + 5));
	_strcpy(str, argv[0]);
	_strcat(str, ": ");
	_strcat(str, num);
	_strcat(str, ": ");
	_strcat(str, sargs[0]);

	if (err == 127)
		_printf(STDERR_FILENO, "%s: not found\n", str);
	else if (err == 126)
		_printf(STDERR_FILENO, "%s: Permission denied\n", str);
	else if (err == 666)
		_printf(STDERR_FILENO, "%s: Illegal number: %s\n", str, sargs[1]);

	free(num);
	free(str);
}
