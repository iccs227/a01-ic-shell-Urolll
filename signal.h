#ifndef SIGNAL_H
#define SIGNAL_H

#include <string.h>
#include <unistd.h>

void set_signals(void);
int signaling_echo_exit(char* buffer);
void handle_signal(int sig);
void set_pid_foreground(pid_t pid);
void kill_foreground(int signal);
void sigchld_handler(int signum);

#endif
