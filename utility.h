#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_CMD_BUFFER 255

void set_signals(void);
void print_otter(void);
int handle_double_bang(char *buffer, const char *last_command, int fileFlag);
int handle_echo(const char *buffer, int fileFlag);
int handle_exit(const char *buffer, int fileFlag);
int handle_clear(const char *buffer);
int handle_otter(const char *buffer);
void print_otter();
void run_external(const char* command, char* const args[]);

#endif
