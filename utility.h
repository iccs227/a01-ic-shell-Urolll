#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#define MAX_CMD_BUFFER 255

void print_otter(void);

int handle_double_bang(char *buffer, const char *last_command, int fileFlag);
int handle_echo(const char *buffer, int fileFlag);
int handle_exit(const char *buffer, int fileFlag);
int handle_clear(const char *buffer);
int handle_otter(const char *buffer);
void print_otter();

#endif
