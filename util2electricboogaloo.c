#include "holberton.h"

/**
 * tokenize - parse buff into tokens
 * @buff: pointer to be tokenized
 *
 * Return: pointer to array of tokens
 */

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
