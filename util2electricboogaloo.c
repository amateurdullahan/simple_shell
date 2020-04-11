#include "holberton.h"

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
