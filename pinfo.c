/*
 * @file pinfo.c
 * @brief Prints system information
 */

#include <unistd.h>
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

    int main(int argc, char *argv[]) {
  // - Take a single command line parameter that is a process identifier
  // - For that process identifier, print out
  // - The process priority
  // - The scheduling method - as a string of text NOT a number
  // - If the process identifier does not exist, print an error message and exit
  // - If the user does NOT specify a process identifier, print the information
  // for the CURRENT executing process

  if (argc == 1) {
    // Print information for the current process
    pid_t pid = getpid();
    int policy = sched_getscheduler(pid);
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
    default:
      policy_str = "UNKNOWN";
      break;
    }

    printf("Results for current process:\n");
    printf("Priority: %d\n", getpriority(PRIO_PROCESS, 0));
    printf("Scheduling method: %s\n", policy_str);
  } else if (argc == 2) {
    // Print information for the specified process
    int pid = atoi(argv[1]);
    int policy = sched_getscheduler(pid);
    if (policy == -1) {
      perror("sched_getscheduler");
      return 1;
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
    default:
      policy_str = "UNKNOWN";
      break;
    }

    printf("Results for process %d:\n", pid);
    printf("Priority: %d\n", getpriority(PRIO_PROCESS, pid));
    printf("Scheduling method: %s\n", policy_str);
  } else {
    fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
    return 1;
  }
}