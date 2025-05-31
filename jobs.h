#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

typedef enum {
  JOB_RUNNING,
  JOB_STOPPED,
  JOB_DONE
} JobState;

typedef struct Job {
  int id;
  pid_t pid;
  char* command;
  JobState state;
  struct Job* next;
} Job;

void initial_jobs(void);
void add_job(pid_t pgid, const char* command, JobState state);
void remove_job(pid_t pgid);
void update_job(pid_t pgid, JobState state);
void print_jobs(void);
void cleanup_jobs();
Job* find_job_by_pid(pid_t pid);
Job* find_job_by_id(int id);
void cleanup_done_jobs(void);

extern Job* job_list;
extern int next_job_id;
extern pid_t foreground_pgid;

#endif
