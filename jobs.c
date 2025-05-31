#include "jobs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

Job* job_list = NULL;
int next_job_id = 1;

// Reset Job List and Next Job ID Counter
void initial_jobs() {
  job_list = NULL;
  next_job_id = 1;
}

// Allocation a New Struct for a New Job
void add_job(pid_t pid, const char *command, JobState state) {
  Job* new_job = malloc(sizeof(Job));
  new_job->id = next_job_id++;
  new_job->pid = pid;
  new_job->command = strdup(command);
  new_job->state = state;
  new_job->next = job_list;
  job_list = new_job;
}

// Remove a Job and Free Memory Allocation
void remove_job(pid_t pid) {
  Job** ptr = &job_list;
  while(*ptr) {
    if ((*ptr)->pid == pid) {
      Job* temp = *ptr;
      *ptr = (*ptr)->next;
      free(temp->command);
      free(temp);
      return;
    }
    ptr = &(*ptr)->next;
  }
}

// Find Job by Process ID and Update its State
void update_job(pid_t pid, JobState state) {
  for (Job *job = job_list; job; job = job->next) {
    if (job->pid == pid) {
      job->state = state;
      return;
    }
  }
}

// Print All Jobs in the List with Description
void print_jobs() {
    if (job_list == NULL) {
        printf("No jobs\n");
        return;
    }
    
    for (Job* job = job_list; job; job = job->next) {
        const char* status = "Unknown";
        switch (job->state) {
            case JOB_RUNNING: status = "Running"; break;
            case JOB_STOPPED: status = "Stopped"; break;
            case JOB_DONE: status = "Done"; break;
        }
        printf("[%d] %%%-4d %s \t %s\n", job->id, job->id, status, job->command);
    }
}

// Free All Jobs and their Commands before Exiting Shell
void cleanup_jobs(void) {
  while (job_list) {
    Job* temp = job_list;
    job_list = job_list->next;
    free(temp->command);
    free(temp);
  }
}

// Locate Job by PID
Job* find_job_by_pid(pid_t pid) {
  for (Job* job = job_list; job; job = job->next) {
    if (job->pid == pid) return job;
  }
  return NULL;
}

// Locate Job by ID
Job* find_job_by_id(int id) {
  for (Job* job = job_list; job; job = job->next) {
    if (job->id == id) return job;
  }
  return NULL;
}

// Iterates over Job List and Remove all Jobs marked as JOB_DONE
// Free Memory for these Jobs
void cleanup_done_jobs(void) {
    Job** ptr = &job_list;
    while (*ptr) {
        Job* current = *ptr;
        if (current->state == JOB_DONE) {
            printf("Done        %s\n", current->command);
            *ptr = current->next;
            free(current->command);
            free(current);
        } else {
            ptr = &current->next;
        }
    }
}
