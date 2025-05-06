/* ICCS227: Project 1: icsh
 * Name: Thanatat Aruntaravanit
 * StudentID: 6580998
 */

/*
CREDIT
------
otter ascii art: https://emojicombos.com/otter-ascii-art
using ANSI escape sequence to clear screen: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
more on using ANSI escape sequence: https://en.wikipedia.org/wiki/ANSI_escape_code
string copy and slicing: https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
*/

#include "stdio.h"
#include "string.h"
#include "utility.h"

int main(int argc, char* argv[]) {
    FILE* input = stdin;
    int fileFlag = 0;
    char buffer[MAX_CMD_BUFFER] = "";
    char last_command[MAX_CMD_BUFFER] = "";

    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            perror("Error opening file");
            return 1;
        }
        fileFlag = 1;
    }

    if (!fileFlag) {
        printf("Welcome to Otter Land!\n");
        printf("Here you can give me commands!\n");
        print_otter();
    } else {
        char* filename = argv[1];
        printf("Welcome to Otter Land!\n");
        printf("Starting with: %s\n", filename);
    }

    while (1) {
        if (!fileFlag) {
            printf("icsh $ ");
            fflush(stdout);
        }

        strcpy(last_command, buffer);
        if (!fgets(buffer, MAX_CMD_BUFFER, input)) {
            if (!fileFlag) printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0 && fileFlag) {
            continue;
        }

        if (handle_double_bang(buffer, last_command, fileFlag)) {
            continue;
        }

        if (handle_echo(buffer, fileFlag)) {
            continue;
        }

        int exit_code = handle_exit(buffer, fileFlag);
        if (exit_code != -1) {
            if (input != stdin) fclose(input);
            return exit_code;
        }

        if (handle_clear(buffer)) {
            continue;
        }

        if (handle_otter(buffer)) {
            continue;
        }

        if (strlen(buffer) > 0) {
            printf("bad command\n");
        }
    }

    if (input != stdin) fclose(input);
    return 0;
}
