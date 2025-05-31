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
#include "jobs.h"
#include "utility.h"
#include "signal.h"
#include <termio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int exit_code = 1;

int main(int argc, char* argv[]) {
    FILE* input = stdin;
    int fileFlag = 0;
    char buffer[MAX_CMD_BUFFER] = "";
    char last_command[MAX_CMD_BUFFER] = "";
    char original_command[MAX_CMD_BUFFER] = "";
    int skip_last_command_update = 0;

    // File Mode Flagging
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            perror("Error opening file");
            return 1;
        }
        fileFlag = 1;
    }

    // Displays a Welcome Message based on File Mode Flagging
    if (!fileFlag) {
        printf("Welcome to Otter Land!\n");
        printf("Here you can give me commands!\n");
        print_otter();
    } else {
        char* filename = argv[1];
        printf("Welcome to Otter Land!\n");
        printf("Starting with: %s\n", filename);
    }

    set_signals();
    initial_jobs();

    // Begin of Main Loop
    while (1) {
        // If a job is done, remove it
        cleanup_done_jobs();

        // Command Prompt for Interactive Mode
        if (!fileFlag) {
            printf("icsh $ ");
            fflush(stdout);
        }

        // Read a Line and Remove Trailing Newline
        if (!fgets(buffer, MAX_CMD_BUFFER, input)) {
            if (!fileFlag) printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        skip_last_command_update = 0;

        strcpy(original_command, buffer);

        // Ignore Empty Line
        if (strlen(buffer) == 0) {
            skip_last_command_update = 1;
            continue;
        }

        // Handling of !!
        int is_double_bang = (strcmp(buffer, "!!") == 0);
        int contains_double_bang = (strstr(buffer, "!!") != NULL);
        
        if (is_double_bang || contains_double_bang) {
            if (strlen(last_command) == 0) {
                if (!fileFlag) printf("No previous command\n");
                skip_last_command_update = 1;
                continue;
            }
            
            if (is_double_bang) {
                strcpy(buffer, last_command);
                exit_code = 0;
                if (!fileFlag) printf("%s\n", buffer);
            }
            else {
                char new_buffer[MAX_CMD_BUFFER] = "";
                char *current = buffer;
                char *bang_pos;
                
                while ((bang_pos = strstr(current, "!!")) != NULL) {
                    strncat(new_buffer, current, bang_pos - current);
                    strcat(new_buffer, last_command);
                    current = bang_pos + 2;
                }
                strcat(new_buffer, current);
                strcpy(buffer, new_buffer);
                
                if (!fileFlag) printf("%s\n", buffer);
            }
            
            skip_last_command_update = 1;
        }

        if (!skip_last_command_update) {
            strcpy(last_command, original_command);
        }

        // Handle Exiting 
        int exit_status = handle_exit(buffer);
        if (exit_status != -1) {
            if (input != stdin) fclose(input);
            cleanup_jobs();
            return exit_status;
        }

        // Handle echo $?
        if (signaling_echo_exit(buffer)) {
            exit_code = 0;
            continue;
        }

        // Handle Clear Command
        if (handle_clear(buffer)) {
            exit_code = 0;
            continue;
        }

        // Handle Otter Command
        if (handle_otter(buffer)) {
            exit_code = 0;
            continue;
        }

        // Handle Jobs
        if (strcmp(buffer, "jobs") == 0) {
            print_jobs();
            exit_code = 0;
            continue;
        }

        // Handle Foreground Job
        if (strncmp(buffer, "fg %", 4) == 0) {
            int job_id = atoi(buffer + 4);
            Job* job = find_job_by_id(job_id);
            if (job) {
                kill(-job->pid, SIGCONT);
                set_pid_foreground(job->pid);
                tcsetpgrp(STDIN_FILENO, job->pid);
                update_job(job->pid, JOB_RUNNING);
        
                int status;
                if (waitpid(job->pid, &status, WUNTRACED) == -1) {
                    perror("waitpid");
                } else {
                    if (WIFEXITED(status)) {
                        exit_code = WEXITSTATUS(status);
                        remove_job(job->pid);
                    } else if (WIFSIGNALED(status)) {
                        exit_code = 128 + WTERMSIG(status);
                        remove_job(job->pid);
                    } else if (WIFSTOPPED(status)) {
                        exit_code = 128 + WSTOPSIG(status);
                        update_job(job->pid, JOB_STOPPED);
                    }
                }      
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
                signal(SIGTTOU, SIG_DFL);
                set_pid_foreground(0);
            } else {
                printf("Job not found\n");
            }
            continue;
        }

        // Handle Background Job
        if (strncmp(buffer, "bg %", 4) == 0) {
            int job_id = atoi(buffer + 4);
            Job* job = find_job_by_id(job_id);
            if (job && job->state == JOB_STOPPED) {
                kill(-job->pid, SIGCONT);
                update_job(job->pid, JOB_RUNNING);
                printf("[%d] %d\n", job->id, job->pid);
            } else {
                printf("Job not found or not stopped\n");
            }
            continue;
        }

        char job_command[MAX_CMD_BUFFER];
        strcpy(job_command, buffer);

        // Split Command Line into Array of Arguments
        char *args[MAX_CMD_BUFFER/2 + 1];
        int arg_count = 0;
        char *token = strtok(buffer, " ");
        
        while (token != NULL && arg_count < MAX_CMD_BUFFER / 2) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
        
        if (arg_count == 0) {
            continue;
        }

        // Handle Echo
        if (strcmp(args[0], "echo") == 0) {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            
            if (handle_redirection(args) != -1) {
                for (int i = 1; args[i] != NULL; i++) {
                    printf("%s", args[i]);
                    if (args[i+1] != NULL) printf(" ");
                }
                printf("\n");
            }
            
            fflush(stdout);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdout);
            close(saved_stdin);
            exit_code = 0;
            continue;
        }

        // Execute Commands that are not built in using fork() and execvp()
        run_external(job_command, args);
    }

    // Clean Up when Exiting
    if (input != stdin) fclose(input);
    cleanup_jobs();
    return 0;
}
