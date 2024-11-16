/*
 * @file finfo.c
 * @brief This program displays the file information about a given file provided
 * via the command line.
 * 
 * Author: Leigh Goetsch
 * Course: CPE 2600
 * Seciton: 121
 * Assignment: Lab 9
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
  switch (file_info.st_mode & S_IFMT) {
  case S_IFREG:
    printf("File type: Regular file\n");
    break;
  case S_IFDIR:
    printf("File type: Directory\n");
    break;
  case S_IFCHR:
    printf("File type: Character device\n");
    break;
  case S_IFBLK:
    printf("File type: Block device\n");
    break;
  case S_IFIFO:
    printf("File type: FIFO\n");
    break;
  case S_IFLNK:
    printf("File type: Symbolic link\n");
    break;
  case S_IFSOCK:
    printf("File type: Socket\n");
    break;
  default:
    printf("File type: Unknown - st_mode = %d\n", file_info.st_mode);
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