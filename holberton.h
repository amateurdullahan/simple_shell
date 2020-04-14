#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>



char **tokenize(char *buff);
char *cmdcall(char **argv, char **env, char **sargs);
char **getsargs(char *buff);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcat(char *dest, char *src);
int chexe(char *cmd, char **sargs, char **env);
void exitbltin(char *buff);
void envbltin(char *buff, char **env);
char *prepbuff();
void pthexp(char *rel, char *dest);
char *trimbuff(char *buff);
int _strlen(char *str);

#endif /* HOLBERTON_H */
