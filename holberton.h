#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>



char **tokenize(char *buff);
int cmdcall(char **argv, char **env);



#endif /* HOLBERTON_H */
