#include <sys/time.h>  // struct timeval, select()
                       // fd_set, FD_ZERO, FD_SET, FD_ISSET
#include <stdio.h>

#define STDIN 0  // file descriptor for standard input

int main(void)
{
  struct timeval tv;
  fd_set read_fds;

  tv.tv_sec = 2;
  tv.tv_usec = 500000;

  FD_ZERO(&read_fds);
  FD_SET(STDIN, &read_fds);

  // don't care about write_fds and except_fds
  select(STDIN+1, &read_fds, NULL, NULL, &tv);

  if (FD_ISSET(STDIN, &read_fds))
    printf("A key was pressed!\n");
  else
    printf("Timed out.\n");

  return 0;
}

