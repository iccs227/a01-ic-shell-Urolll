#include "utility.h"
#include "signal.h"
#include "jobs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

extern int exit_code;

// Logic for !!
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

// Logic for echo
int handle_echo(const char *buffer) {
    if (strncmp(buffer, "echo ", 5) == 0) {
        printf("%s\n", buffer + 5);
        return 1;
    }
    return 0;
}

// Logic for exit
int handle_exit(const char *buffer) {
    if (strncmp(buffer, "exit", 4) == 0) {
        int code = 0;
        sscanf(buffer, "exit %d", &code);
        // Mask the Exit Code to be within Range
        code &= 0xFF;
        printf("exiting with %d\n", code);
        return code;
    }
    return -1;
}

// Logic for clear
int handle_clear(const char *buffer) {
    if (strcmp(buffer, "clear") == 0) {
        printf("\033[2J\033[H");
        return 1;
    }
    return 0;
}

// Checks for otter as buffer
int handle_otter(const char *buffer) {
    if (strcmp(buffer, "otter") == 0) {
        print_otter();
        return 1;
    }
    return 0;
}

// Logic for Printing Otter ASCII Art
void print_otter() {
    // Randomize between 3 Arts Equally
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

// Run External Commands by forking and using execvp()
void run_external(const char* job_command, char* args[]) {
    int background = 0;
    int i = 0;
    while (args[i]) i++;
    if (i > 0 && strcmp(args[i-1], "&") == 0) {
        background = 1;
        args[i-1] = NULL;
    }

    pid_t pid = fork();
    if (pid == 0) {
        setpgid(0, 0);
        
        if (!background) {
            tcsetpgrp(STDIN_FILENO, getpgid(0));
        } else {
            int null_fd = open("/dev/null", O_RDONLY);
            if (null_fd > 0) {
                dup2(null_fd, STDIN_FILENO);
                close(null_fd);
            }
        }
        
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        
        if (handle_redirection(args) == -1) {
            exit(1);
        }
        
        execvp(args[0], args);
        printf("bad command\n");
        exit(1);
    } else {
        setpgid(pid, pid);
        
        add_job(pid, job_command, background ? JOB_RUNNING : JOB_RUNNING);
        
        if (background) {
            Job* job = find_job_by_pid(pid);
            if (job) {
                printf("[%d] %d\n", job->id, pid);
            }
        } else {
            set_pid_foreground(pid);
            tcsetpgrp(STDIN_FILENO, pid);
            
            int status;
            while (1) {
                if (waitpid(pid, &status, WUNTRACED) == -1) {
                    perror("waitpid");
                    break;
                }
                
                if (WIFEXITED(status)) {
                    exit_code = WEXITSTATUS(status);
                    remove_job(pid);
                    break;
                } else if (WIFSIGNALED(status)) {
                    exit_code = 128 + WTERMSIG(status);
                    remove_job(pid);
                    break;
                } else if (WIFSTOPPED(status)) {
                    exit_code = 128 + WSTOPSIG(status);
                    update_job(pid, JOB_STOPPED);
                    printf("\n[%d] Stopped\n", pid);
                    break;
                }
            }
            
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
            signal(SIGTTOU, SIG_DFL);
            set_pid_foreground(0);
        }
    }
}

// Handle the Logic of Redirection
int handle_redirection(char* args[]) {
    int i = 0;
    int input_fd = -1, output_fd = -1;
    char* input_file = NULL, *output_file = NULL;
    int append_mode = 0;

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
            append_mode = 0;
        } else if (strcmp(args[i], ">>") == 0) {
            if (!args[i+1]) {
                printf("Missing output file\n");
                return -1;
            }
            output_file = args[i+1];
            args[i] = NULL;
            i++;
            append_mode = 1;
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
        int flags = O_WRONLY | O_CREAT;
        if (append_mode) {
            flags |= O_APPEND;
        } else {
            flags |= O_TRUNC;
        }
        
        output_fd = open(output_file, flags, 0644);
        if (output_fd < 0) {
            perror("Error opening output file");
            return -1;
        }
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    return 0;
}
