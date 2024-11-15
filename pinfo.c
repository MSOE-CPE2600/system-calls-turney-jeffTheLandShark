/*
 * @file pinfo.c
 * @brief Prints the priority and scheduling method of a process
 */

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void print_pinfo(pid_t pid);

int main(int argc, char *argv[]) {

  if (argc == 1) {
    // Print information for the current process
    pid_t pid = getpid();
    print_pinfo(pid);
  } else if (argc == 2) {
    // Print information for the specified process
    int pid = atoi(argv[1]);
    print_pinfo(pid);

  } else {
    fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
  }
  return 0;
}

void print_pinfo(pid_t pid) {
  // get priority
  int priority = getpriority(PRIO_PROCESS, pid);

  // get scheduling policy
  int policy = sched_getscheduler(pid);

  if (policy == -1) {
    perror("sched_getscheduler");
    exit(1);
  }

  char *policy_str;
  switch (policy) {
  case SCHED_OTHER:
    policy_str = "SCHED_OTHER";
    break;
  case SCHED_FIFO:
    policy_str = "SCHED_FIFO";
    break;
  case SCHED_RR:
    policy_str = "SCHED_RR";
    break;
  case SCHED_BATCH:
    policy_str = "SCHED_BATCH";
    break;
  case SCHED_ISO:
    policy_str = "SCHED_ISO";
    break;
  case SCHED_IDLE:
    policy_str = "SCHED_IDLE";
    break;
  case SCHED_DEADLINE:
    policy_str = "SCHED_DEADLINE";
    break;
  default:
    policy_str = "UNKNOWN";
    break;
  }

  printf("Results for process %d:\n", pid);
  printf("Priority: %d\n", priority);
  printf("Scheduling method: %s\n", policy_str);
}