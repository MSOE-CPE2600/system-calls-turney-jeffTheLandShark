/*
 * @file pmod.c
 * @brief This program modifies its own priority to reduce it by 10, sleeps for
 * 1,837,272,638 nano seconds, prints a goodbye message, and exits.
 *
 * Author: Leigh Goetsch
 * Course: CPE 2600
 * Seciton: 121
 * Assignment: Lab 9
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  nice(10);
  
  struct timespec ts;
  ts.tv_sec = 1;
  ts.tv_nsec = 837272638;
  nanosleep(&ts, NULL);

  printf("Goodbye!\n");

  return 0;
}