/*
 * @file info.c
 * @brief Prints system information
 */

#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);

  printf("Example of system information\n\n");
  printf("1. The current time of day - in nanoseconds\n");
  printf("Current time: %.2f nanoseconds\n",
         ts.tv_nsec + (ts.tv_sec * 1000000000.0));
  printf("\n");

  struct utsname uts;
  uname(&uts);

  printf("2. The system's network name\n");
  printf("Network name: %s\n", uts.nodename);
  printf("\n");
  printf("3. The operating system name\n");
  printf("Operating system: %s\n", uts.sysname);
  printf("\n");
  printf("4. The operating system release and version\n");
  printf("Release: %s\n", uts.release);
  printf("\n");
  printf("5. The system's hardware type\n");
  printf("Hardware type: %s\n", uts.machine);
  printf("\n");
  printf("6. The number of CPUs on the system\n");
  printf("Number of CPUs: %d\n", get_nprocs());
  printf("\n");
  printf("7. The total amount of physical memory IN BYTES\n");
  printf("Total memory: %ld\n", get_phys_pages() * getpagesize());
  printf("\n");
  printf("8. The total amount of free memory IN BYTES\n");
  struct sysinfo si;
  sysinfo(&si);
  printf("Free memory: %ld\n", si.freeram);

  return 0;
}
