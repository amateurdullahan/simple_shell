#include "holberton.h"

/**
 * _printf - prinnt string passed
 * @format: string being passed to be printed
 *
 * Return: char count
 */

int _printf(const char *format, ...)
{

  va_list vat;
  int len;
  len = 0;

  if (format == NULL || vat == NULL)
    return (-1);
  va_start(vat, format);
  while (*format != '\0')
    {
      if (*format != '%')
	{
	  _putchar(*format);
	  format++;
	  len++;
	  continue;
	}
      else if (*format == '\0')
	break;
      len += print_conv(format, vat);
      format++;
      format++;
    }
  va_end(vat);
  return (len);
}

/**
 * _puts - Prints the string using _putchar
 * @str:  Input string
 *
 * Return: string printed
 */
void _puts(char *str)
{
  while (*str != '\0')
    {
      _putchar(*str);
      str++;
    }
}

/**
 * _putchar - writes char to stdout
 * @c: input char
 *
 * Return: Char printed to stdout;
 */
int _putchar(char c)
{
  return (write(1, &c, 1));
}

/**
 * print_conv - takes string and use correct conversion
 * @str: input string
 * @arg: input argument from list
 *
 * Return: count
 */

int print_conv(const char *str, va_list arg)
{
  int count, c;
  char *s = malloc(sizeof(str));

  count = 0;
  str++;
  switch (*str)
    {
    case 's':
      count = (print_s(str, arg));
      free(s);
      return (count);
    case 'c':
      c = va_arg(arg, int);
      _putchar(c);
      count++;
      free(s);
      return (count);
    case 'd':
      s = _itoa(va_arg(arg, int), s, 10);
      _puts(s);
      count += _strlen(s);
      free(s);
      return (count);
    case 'i':
      s = _itoa(va_arg(arg, int), s, 10);
      _puts(s);
      count += _strlen(s);
      free(s);
      return (count);
    default:
      _putchar('%');
      _putchar(*str);
      count = 2;
      free(s);
      return (count);
    }
}

/**
 * print_s - prints tring after conversion specifier
 * @str: input string
 * @arg: input argument
 *
 * Return: length of string
 */

int print_s(const char *str, va_list arg)
{
  char *s;
  int count;

  s = va_arg(arg, char *);
  if (s == NULL)
    {
      return (0);
    }
  else
    {
      _puts(s);
      count = _strlen(s);
    }
  return (count);
}
