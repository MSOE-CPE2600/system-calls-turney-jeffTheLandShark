/*
 * @file finfo.c
 * @brief This program displays the file information about a given file provided
 * via the command line.
 */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

// Write a program(finfo.c / finfo) that displays the file information about a
// given file provided via the command line .The file name MUST be specified via
// the command line.Specifically,
//   -The type of file - print this in a user readable way
//  - The permissions set on the file - print these in a user readable way
//  - The owner of the file - printing the user identifier(number) is enough
// - The size of the file IN BYTES
// - The date and time of last modification (format this for easy viewing, do
// NOT print out raw bytes or a large integer).
// - If at any point, there is an error print an error and exit.

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  // get file info
  struct stat file_info;
  if (stat(argv[1], &file_info) == -1) {
    perror("stat");
    return 1;
  }

  // print file type
  if (S_ISREG(file_info.st_mode)) {
    printf("File type: Regular file\n");
  } else if (S_ISDIR(file_info.st_mode)) {
    printf("File type: Directory\n");
  } else if (S_ISCHR(file_info.st_mode)) {
    printf("File type: Character device\n");
  } else if (S_ISBLK(file_info.st_mode)) {
    printf("File type: Block device\n");
  } else if (S_ISFIFO(file_info.st_mode)) {
    printf("File type: FIFO/pipe\n");
  } else if (S_ISLNK(file_info.st_mode)) {
    printf("File type: Symbolic link\n");
  } else if (S_ISSOCK(file_info.st_mode)) {
    printf("File type: Socket\n");
  } else {
    printf("File type: Unknown\n");
  }

  // print permissions
  printf("Permissions: ");
  printf((file_info.st_mode & S_IRUSR) ? "r" : "-");
  printf((file_info.st_mode & S_IWUSR) ? "w" : "-");
  printf((file_info.st_mode & S_IXUSR) ? "x" : "-");
  printf((file_info.st_mode & S_IRGRP) ? "r" : "-");
  printf((file_info.st_mode & S_IWGRP) ? "w" : "-");
  printf((file_info.st_mode & S_IXGRP) ? "x" : "-");
  printf((file_info.st_mode & S_IROTH) ? "r" : "-");
  printf((file_info.st_mode & S_IWOTH) ? "w" : "-");
  printf((file_info.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");

  // print owner
  printf("Owner: %d\n", file_info.st_uid);

  // print size
  printf("Size: %ld bytes\n", file_info.st_size);

  // print last modification time
  printf("Last modification time: %s", ctime(&file_info.st_mtime));

  fclose(file);
  return 0;
}