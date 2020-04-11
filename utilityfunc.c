#include "holberton.h"

/**
 * _strlen - find length of given stirng
 * @str: string to find length of
 *
 * Return: length of string less the null char
 */

int _strlen(char *str)
{
	int count;

	if (str == NULL)
		return (0);

	for (count = 0; str[count]; count++)
		;

	return (count);
}

/**
 * _strcpy - copies src string to dest string
 * @dest: destination of copying
 * @src: string to be copied
 *
 * Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int c;

	for (c = 0; src[c]; c++)
	{
		dest[c] = src[c];
	}
	dest[c] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if same OR -1 if different
 */

int _strcmp(char *s1, char *s2)
{
	int c, r = 0;

	for (c = 0; s1[c] != '\0' && s2[c] != '\0'; c++)
	{
		if (s1[c] != s2[c])
		{
			r = (s1[c] - s2[c]);
			return (r);
		}
	}
	return (r);
}

/**
 * _strncmp - comapres two string to the nth character
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 *
 * Return: 0 if same or -1 if different
 */

int _strncmp(char *s1, char *s2, int n)
{
	int c, r = 0;

	for (c = 0; c < n && s1[c] != '\0' && s2[c] != '\0'; c++)
	{
		if (s1[c] != s2[c])
		{
			r = (s1[c] - s2[c]);
			return (r);
		}
	}
	return (r);
}

/**
 * _strcat - appends src string to dest string
 * @dest: string being appened
 * @src: string to be appended to dest
 *
 * Return: appended dest string
 */

char *_strcat(char *dest, char *src)
{
	int c, d;

	for (c = 0; dest[c]; c++)
		;
	for (d = 0; src[d] != '\0'; d++, c++)
		dest[c] = src[d];
	dest[c] = '\0';
	return (dest);
}
