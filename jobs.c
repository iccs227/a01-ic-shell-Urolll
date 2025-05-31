#include "jobs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

Job* job_list = NULL;
int next_job_id = 1;

void initial_jobs() {
  job_list = NULL;
  next_job_id = 1;
}

void add_job(pid_t pid, const char *command, JobState state) {
  Job* new_job = malloc(sizeof(Job));
  new_job->id = next_job_id++;
  new_job->pid = pid;
  new_job->command = strdup(command);
  new_job->state = state;
  new_job->next = job_list;
  job_list = new_job;
}

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

void update_job(pid_t pid, JobState state) {
  for (Job *job = job_list; job; job = job->next) {
    if (job->pid == pid) {
      job->state = state;
      return;
    }
  }
}

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

void cleanup_jobs(void) {
  while (job_list) {
    Job* temp = job_list;
    job_list = job_list->next;
    free(temp->command);
    free(temp);
  }
}

Job* find_job_by_pid(pid_t pid) {
  for (Job* job = job_list; job; job = job->next) {
    if (job->pid == pid) return job;
  }
  return NULL;
}

Job* find_job_by_id(int id) {
  for (Job* job = job_list; job; job = job->next) {
    if (job->id == id) return job;
  }
  return NULL;
}

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
