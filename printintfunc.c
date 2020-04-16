#include "holberton.h"

/**
 * _itoa - convert integer to string
 * @value: value to be converted to a string
 * @buffer: array to store result
 * @base: numerical base
 *
 * Return: pointer to resulting null-term string
 */

char *_itoa(int value, char *buffer, int base)
{
	int i = 0;
	int n = _abs(value);
	int r;

	if (base < 2 || base > 32)
		return (buffer);
	while (n)
	{
		r = n % base;
		if (r >= 10)
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;
		n = n / base;
	}
	if (i == 0)
		buffer[i++] = '0';
	if (value < 0 && base == 10)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (_reverse(buffer, 0, i - 1));
}

/**
 * _abs - printing absolute value of integer
 * @a: char to check value of
 *
 * Return: prints absolute value of numbers
 */

int _abs(int a)
{
	if (a >= 0)
		return (a);
	else
		return (a - (a * 2));
}

/**
 * _reverse - Reverses buffer[i..j]
 * @buffer: buffer to be reversed
 * @i: first location in buffer
 * @j: ending location
 *
 * Return: pointer to reversed buffer
 */

char *_reverse(char *buffer, int i, int j)
{
	while (i < j)
		_swap(&buffer[i++], &buffer[j--]);
	return (buffer);
}

/**
 * _swap - Swaps two numbers
 * @x: first number
 * @y: second number
 *
 * Return: void
 */

void _swap(char *x, char *y)
{
	char t = *x;

	*x = *y;
	*y = t;
}

/**
 * _atoi - converts string to integer
 * @s: string to convert
 *
 * Return: converted string
 */

int _atoi(char *s)
{
	int i, j, n, m;

	i = n = 0;
	m = 1;
	while ((*(s + i) < '0' || *(s + i) > '9') && (*(s + i) != '\0'))
	{
		if (*(s + i) == '-')
			m *= -1;
		i++;
	}
	j = i;
	while ((*(s + j) >= '0') && (*(s + j) <= '9'))
	{
		n = n * 10 + m * (*(s + j) - '0');
		j++;
	}
	return (n);
}
