#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

extern int errno;

char **tokenize(char *buff, char delim);
char *cmdcall(char **argv, char **env, char **sargs, int line);
char **getsargs(char *buff);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcat(char *dest, char *src);
int chexe(char *cmd, char **sargs, char **env);
void exitbltin(char *buff, char **argv, int line);
void envbltin(char *buff, char **env);
char *prepbuff();
void pthexp(char *rel, char *dest);
char *trimbuff(char *buff);
int _strlen(char *str);
char *afterpath(char **sargs, char **argv, int line);
void prerr(char **argv, char **sargs, int line, int err);

/* PRINTF FUNCTIONS */

int _printf(int fd, const char *format, ...);
void _puts(int fd, char *str);
int _putchar(int fd, char c);
char *_itoa(int value, char *buffer, int base);
int _abs(int a);
char *_reverse(char *buffer, int i, int j);
void _swap(char *x, char *y);
int print_conv(int fd, const char *str, va_list arg);
int print_s(int fd, va_list arg);
int _atoi(char *s);

#endif /* HOLBERTON_H */
