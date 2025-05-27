#include "utility.h"
#include "signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

extern int exit_code;

int handle_double_bang(char *buffer, const char *last_command, int fileFlag) {
    if (strcmp(buffer, "!!") == 0) {
        if (strlen(last_command) == 0) {
            if (!fileFlag) {
                printf("No previous command\n");
            }
            return 1;
        }
        strcpy(buffer, last_command);
        if (!fileFlag) {
            printf("%s\n", buffer);
        }
    }
    return 0;
}

int handle_echo(const char *buffer, int fileFlag) {
    if (strncmp(buffer, "echo ", 5) == 0) {
        printf("%s\n", buffer + 5);
        return 1;
    }
    return 0;
}

int handle_exit(const char *buffer, int fileFlag) {
    if (strncmp(buffer, "exit", 4) == 0) {
        int code = 0;
        sscanf(buffer, "exit %d", &code);
        code &= 0xFF;
        printf("exiting with %d\n", code);
        return code;
    }
    return -1;
}

int handle_clear(const char *buffer) {
    if (strcmp(buffer, "clear") == 0) {
        printf("\033[2J\033[H");
        return 1;
    }
    return 0;
}

int handle_otter(const char *buffer) {
    if (strcmp(buffer, "otter") == 0) {
        print_otter();
        return 1;
    }
    return 0;
}

void print_otter() {
    int r = rand() % 3;
    if (r == 0) {
        printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⠿⠛⠛⠛⠉⠉⠉⠉⠀⠀⠉⠉⠉⠛⠛⠿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⣦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⠷⣶⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⢀⣠⣴⡾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣻⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⢠⣿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣀⣀⣀⠀⠀⠀⠀⠀⠘⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⢻⣿⣶⢶⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⢼⡿⠟⠛⠛⠿⠀⠀⠀⠀⠀⠘⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠉⠻⢷⣿⠇⠀⠀⠀⠀⢀⣴⡿⠿⠿⠿⠇⠀⠀⠀⢾⣿⣿⣿⣟⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣧⠀⠀⠀⠀⣀⣀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⣾⡟⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⣿⠛⠁⠀⠀⠀⠀⠀⠀⠸⡇⠀⠀⠀⠀⠶⠚⠛⠛⠿⢿⣿⣿⣷⣾⠟⢻⣷⣀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⣿⠃⠀⣀⣀⠀⠀⠀⠀⠀⢸⣷⠀⠀⠀⠀⠀⠀⠀⠀⣿⣄⡀⠀⠀⠀⠀⠀⣀⣼⠇⠀⠀⠀⠀⢤⣤⣄⣀⠀⢸⣿⡿⠀⠀⠀⠈⠛⣿⡇\n");
        printf("⠀⠀⠀⠀⠀⣸⣿⠟⠛⠉⠉⠁⠀⠀⠀⠀⠘⢿⣦⣄⣀⣀⣀⣠⣴⠞⠉⠙⠛⢿⣶⠶⠶⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠉⠙⢷⣾⠟⠁⠀⠀⠀⠀⠀⣿⡅\n");
        printf("⠀⠀⠀⣴⠟⢻⡇⠀⠀⣠⡴⠖⠀⠀⠀⠀⠀⠀⠉⠉⠛⠛⠛⠻⣧⡀⠀⠀⢀⣴⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⢀⣿⠏\n");
        printf("⠀⠀⠈⠁⠀⢸⣇⣴⠞⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠷⠾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠁⠀⠀⠀⠀⠀⠀⠀⣾⠃⠀\n");
        printf("⠀⠀⠀⠀⠀⢠⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠃⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠀⠀\n");
        printf("⠀⠀⠀⠀⢠⡿⠉⢿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⠁⠀⠀\n");
        printf("⠀⠀⠀⠀⠘⠀⠀⢸⣿⠻⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⠃⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⢠⣿⠃⠀⠀⠈⠓⠒⢦⠰⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠃⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⢠⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠃⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⢠⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠁⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⢀⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⢀⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⣠⣾⠟⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠈⢿⣇⡀⠀⠀⠀⢀⣠⣴⣶⡿⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠈⠻⢷⣶⣶⣿⠿⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠀⠀      \n");
    }
    else if (r == 1) {
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣤⣤⣴⣶⣶⣶⣦⣤⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⡾⠿⠛⠛⠋⠉⠉⠉⠉⠉⠉⡉⠉⠉⠉⠛⠛⠿⢷⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⡿⠟⠋⠁⠀⢀⡀⠀⠀⢰⡆⠀⠀⠀⢸⡇⠀⠀⠀⣀⠀⠀⠀⠈⠙⠻⢿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡿⠛⠁⠀⠀⠀⠀⠀⢸⣿⠀⠀⢸⡇⠀⠀⠀⢸⡇⠀⠀⠀⣿⡆⠀⠀⠀⠀⠀⠀⠉⠻⢷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⢀⣠⣴⣶⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⢸⡇⠀⠀⠀⢸⡇⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠿⣶⣦⣄⡀⠀⠀⠀⠀\n");
        printf("⠀⠀⢠⣾⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠀⠀⠸⡧⠀⠀⠀⠘⠃⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀⠀\n");
        printf("⠀⠀⢻⣿⣶⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣶⣶⣿⠏⠀⠀\n");
        printf("⠀⠀⠀⠙⠿⣷⣾⡇⠀⠀⠀⠀⠀⠀⢀⣤⣤⣄⠀⠀⠀⠀⠀⠀⠀⠉⠘⠃⠀⠀⠀⠀⠀⠀⢀⣤⣦⣤⡀⠀⠀⠀⠀⠀⠀⢻⣷⣾⠟⠋⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⣸⡿⠁⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡧⠀⠀⠀⠰⣶⣶⣾⣾⣷⣶⣶⠄⠀⠀⠀⣿⣿⣿⣿⡷⠀⠀⠀⠀⠀⠀⠈⣿⣇⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⣰⡿⠁⠀⠀⠀⠀⠀⠀⠀⠙⠻⠟⠛⠁⠀⠀⠀⠀⠈⠛⠻⣿⠟⠋⠀⠀⠀⠀⠀⠙⠛⠛⠛⠁⠀⠀⠀⠀⠀⠀⠀⠘⣿⡄⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⣰⣿⠷⠶⠖⠒⠲⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠶⠶⠶⠶⣿⣿⣦⠀⠀⠀\n");
        printf("⢀⡴⠿⣿⡏⠀⠀⢀⣠⣤⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⡿⠿⢿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣀⡀⠀⠀⠀⢹⣿⡟⢦⡀\n");
        printf("⠉⠀⠸⣿⣇⣤⡾⠛⢉⣠⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣿⠟⠁⠀⠀⠀⠈⠛⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⣠⣤⡀⠉⠛⠷⣦⣄⣸⣿⡇⠀⠈\n");
        printf("⠀⠀⠀⣿⣿⡋⠀⠀⣿⣿⡿⠙⠻⢶⣦⣄⠀⠀⠀⠀⠈⠙⣿⣆⠀⠀⠀⠀⠀⣰⡿⠉⠁⠀⠀⠀⢀⣠⣴⡾⠋⢿⣿⣷⠀⠀⠈⢙⣿⣿⡇⠀⠀\n");
        printf("⠀⢀⣾⠛⣿⣷⡀⠀⢿⣧⠀⠀⠀⠀⠀⠙⢷⣄⠀⠀⠀⠀⠘⣿⣆⣀⣀⣀⣰⡿⠁⠀⠀⠀⠀⣰⡿⠋⠁⠀⠀⠈⢹⣿⠀⠀⢀⣾⣿⠛⣷⠀⠀\n");
        printf("⠀⠸⠁⠀⠈⣿⣿⣶⣼⣿⣇⠀⠀⠀⠀⠀⠈⢿⣆⠀⠀⠀⠀⠀⠙⠛⠋⠛⠋⠀⠀⠀⠀⢀⣾⠟⠀⠀⠀⠀⠀⢀⣿⡏⢀⣤⣾⣟⠁⠀⠈⠇⠀\n");
        printf("⠀⠀⠀⠀⠀⣿⡇⠉⠻⣿⡿⠀⠀⠀⠀⠀⠀⠘⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡏⠀⠀⠀⠀⠀⠀⢸⣿⣶⡿⠛⢻⣿⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⢠⣿⡇⠀⣸⣿⠁⠀⠀⠀⠀⠀⠀⠀⢹⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠀⠀⠀⠀⠀⠀⠀⠘⣿⣏⠀⠀⢸⣿⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⢸⣿⠀⠐⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⠆⠀⠈⣿⡆⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣷⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⢰⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡆⠀⠀⠀\n");
        printf("⠀⠀⠀⣼⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣧⠀⠀⠀\n");
        printf("⠀⠀⢰⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠿⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡄⠀⠀\n");
        printf("⠀⠀⣼⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀\n");
        printf("⠀⠀⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀\n");
        printf("⠀⠀⢿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡷⠀⠀\n");
    }
    else { 
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠶⠗⠲⠶⣦⣀⣤⠾⠗⠶⢦⣄⠀⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠁⠀⠀⠀⠀⠈⢿⠁⠀⠀⠀⠀⠘⣧⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡤⢀⠀⠀⠀⠀⢸⣆⠀⠀⠀⠀⠰⣿⠀⠀⠀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣿⠶⠆⢦⢠⡴⠛⠉⠛⠶⣤⠀⠾⠷⠦⣤⡀⠀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣤⣤⣤⣤⣤⣤⣴⡟⠉⠀⠀⠀⠀⠙⢧⡀⠀⠀⠀⣻⠁⠀⠀⠀⠈⢻⡄\n");
        printf("⣀⣀⢀⣠⣤⢶⣟⠻⣯⣹⢹⣶⢩⢷⡮⣝⣯⣿⡀⠀⠀⠀⠀⠀⢠⣞⡿⠶⠦⣾⡃⠀⠀⠀⠀⠀⢸⡇\n");
        printf("⢭⣫⠯⡝⡼⢎⡿⣍⢷⡭⣣⠿⣭⢞⡳⣝⢶⣹⣷⣤⣀⣀⣐⣾⣿⠏⠀⠀⠀⠈⢻⣆⡀⠀⢀⣠⠟⠁\n");
        printf("⣿⣙⢮⡝⢧⣛⡼⣚⢮⡜⣧⢻⡼⣭⢳⡝⣮⢳⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠈⣿⢙⡛⢿⡁⠀⠀\n");
        printf("⣧⢛⡞⣼⢣⢏⡶⣹⢮⡝⣮⢳⡳⣎⢷⡻⣭⣷⣾⣿⣿⠿⣿⣟⣿⣧⡀⠀⠀⠀⢠⡟⠐⡀⠈⣷⠀⠀\n");
        printf("⣎⢿⣹⣶⣿⣿⣿⣿⣷⣽⣚⡧⣟⡭⣗⣻⢼⣿⣹⠿⣿⣦⡌⠹⣾⣿⡿⣶⣦⣶⡟⠁⠠⠑⡀⣿⠀⠀\n");
        printf("⢮⣻⡟⠉⣠⣿⡿⢿⣿⣶⣹⡾⠿⢛⣛⣻⠷⣿⣿⣶⣿⣿⣦⡀⢹⡿⣿⣿⣿⣎⣿⣷⢦⣴⣴⠃⠀⠀\n");
        printf("⢯⣿⠁⠸⣿⣿⣷⣾⣿⠛⠉⠐⢿⣿⣿⡿⠀⢠⡿⣿⣿⣻⣿⠃⣤⣤⣾⣿⣿⣿⣟⣷⡄⠀⠀⠀⠀⠀\n");
        printf("⠛⠉⠀⠠⣿⣿⣟⣿⡿⠀⢶⣄⣀⣽⠿⢤⠶⠟⠀⠈⠙⠛⠁⠠⣿⣭⣤⣿⣿⣳⣟⣾⣿⠀⠀⠀⠀⠀\n");
        printf("⣤⣤⣶⣦⡈⠛⠛⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣸⣿⣿⣿⣿⣼⣿⠀⠀⠀⠀⠀\n");
        printf("⣭⣬⣷⡾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣿⣿⣿⣿⡻⣿⣿⠀⠀⠀⠀⠀\n");
        printf("⣿⡉⢡⠀⠴⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⢀⣤⣶⣿⣿⣿⣿⣿⢿⣿⣷⡘⢷⡀⠀⠀⠀⠀\n");
        printf("⠈⠙⠳⣦⣬⣴⣬⣽⣻⣯⣿⣭⣿⣭⣦⣽⣶⣷⣿⣿⣿⣿⣿⣿⢿⣻⢟⡾⣯⣟⣿⣿⡌⢻⡄⠀⠀⠀\n");
        printf("⠀⠀⢀⣽⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠍⠑⠒⠒⠋⠙⠙⠻⢿⣭⡿⡽⣯⣟⣳⣟⣾⡏⠹⣦⣹⡆⠀⠀\n");
        printf("⠀⢠⡿⣯⠷⣯⢿⡿⣽⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⡵⢯⠷⣯⣿⠀⠀⠈⠋⠀⠀⠀\n");    }
    return;
}

void run_external(const char* command, char* args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        setpgid(0, 0);
        tcsetpgrp(STDIN_FILENO, getpgid(0));
              
        if (handle_redirection(args) == -1) exit(1);
        execvp(command, args);
        printf("bad command\n");
        exit(1);
        
    } else {
        setpgid(pid, pid);
        tcsetpgrp(STDIN_FILENO, pid);
        int status;
        set_pid_foreground(pid);
        
        while (1) {
            if (waitpid(pid, &status, WUNTRACED) == -1) {
                perror("waitpid");
                break;
            }
            
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
                break;
            }
            
            if (WIFSTOPPED(status)) {
                printf("\n[%d] Stopped\n", pid);
                exit_code = 128 + WSTOPSIG(status);
                break;
            }
        }
        
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
        signal(SIGTTOU, SIG_DFL);
        
        set_pid_foreground(0);
    }
}

int handle_redirection(char* args[]) {
    int i = 0;
    int input_fd = -1, output_fd = -1;
    char* input_file = NULL, *output_file = NULL;

    while (args[i]) {
        if (strcmp(args[i], "<") == 0) {
            if (!args[i+1]) {
                printf("Missing input file\n");
                return -1;
            }
            input_file = args[i+1];
            args[i] = NULL;
            i++;
        } else if (strcmp(args[i], ">") == 0) {
            if (!args[i+1]) {
                printf("Missing output file\n");
                return -1;
            }
            output_file = args[i+1];
            args[i] = NULL;
            i++;
        }
        i++;
    }

    if (input_file) {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd < 0) {
            perror("Error opening input file");
            return -1;
        }
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }

    if (output_file) {
        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd < 0) {
            perror("Error opening output file");
            return -1;
        }
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    return 0;
}
