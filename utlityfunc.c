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

char *_strcpy(char **dest, char *src)
{
  int c;
  *dest = malloc(sizeof(char) * (_strlen(src) + 1));
  for (c = 0; src[c]; c++)
    {
      (*dest)[c] = src[c];
    }
  (*dest)[c] = '\0';
  return (*dest);
}

int _strcmp(char *s1, char *s2)
{
  int c;
 for (c = 0; s1[c] == '\0' || s2[c] == '\0'; c++)
   {
     if (s1[c] != s2[c])
       {
	 return (-1);
       }
   }
 return (0);
}

int _strncmp(char *s1, char *s2, int n)
{
  int c;
  for (c = 0; c < n || s1[c] != '\0' || s2[c] != '\0'; c++)
    {
      if (s1[c] != s2[c])
	{
	  return (-1);
	}
    }
  return (0);
}






int main(void)
{
  char *a;
  char *b = "foopopgizu";  

int c = _strlen("Holberton");


  printf("%d\n", c);
  c = _strlen(NULL);
  printf("%d\n", c);
  _strcpy(&a, b);
  printf("dest:%s\nsrc:%s\n", a, b);
  return(0);
}
