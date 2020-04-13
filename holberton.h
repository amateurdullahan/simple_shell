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


char **tokenize(char *buff);
char *cmdcall(char **argv, char **env, char *buff, char **sargs);
char **getsargs(char *buff);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcat(char *dest, char *src);
int chexe(char *cmd, char **sargs, char **env);
void exitbltin(char *buff);
void envbltin(char *buff, char **env);
char *prepbuff();

/* PRINTF FUNCTIONS */

int _printf(const char *format, ...);
void _puts(char *str);
int _putchar(char c);
char *_itoa(int value, char *buffer, int base);
int _abs(int a);
char *_reverse(char *buffer, int i, int j);
void _swap(char *x, char *y);
int print_conv(const char *str, va_list arg);
int print_s(const char *str, va_list arg);


#endif /* HOLBERTON_H */
