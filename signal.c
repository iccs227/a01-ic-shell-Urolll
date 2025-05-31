#include "signal.h"
#include "jobs.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

extern int exit_code;
static pid_t foreground_pid = 0;

void set_pid_foreground(pid_t pid) {
    foreground_pid = pid;
}

void kill_foreground(int signal) {
    if (foreground_pid > 0) {
        kill(foreground_pid, signal);
    }
}

void handle_signal(int sig) {
    if (foreground_pid > 0) {
        kill(-foreground_pid, sig);
    }
}


void set_signals(void) {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    
    struct sigaction sa_chld = {
        .sa_handler = sigchld_handler,
        .sa_flags = SA_RESTART | SA_NOCLDSTOP
    };
    sigaction(SIGCHLD, &sa_chld, NULL);
    
    signal(SIGTTOU, SIG_IGN);
}

int signaling_echo_exit(char *buffer) {
    if (strcmp(buffer, "echo $?") == 0) {
        printf("%d\n", exit_code);
        return 1;
    }
    return 0;
}

void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        if (pid == foreground_pid) continue;
        
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            update_job(pid, JOB_DONE);
        } else if (WIFSTOPPED(status)) {
            update_job(pid, JOB_STOPPED);
        } else if (WIFCONTINUED(status)) {
            update_job(pid, JOB_RUNNING);
        }
    }
}
