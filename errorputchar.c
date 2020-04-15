#include "holberton.h"

/**
 * errorputchar - putchar that outputs to stderr
 * @c: char to be put
 *
 * Return: write
 */

int errorputchar(char c)
{
  return (write(2, &c, 1));
}
