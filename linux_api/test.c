#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ipv4_sockets.h"

int main(int argc, char *argv[])
{
  int sv_fd = ipv4_listen(argv[1], 5);
  int cl_fd;
  int read_cnt;
  int send_cnt;
  char buf[80];

  for ( ; ; ) {

    cl_fd = accept(sv_fd, NULL, NULL);
    printf("accept connection! (%d)\n", cl_fd);

    for ( ; ; ) {

      read_cnt = read(cl_fd, buf, sizeof(buf));
      printf("read_cnt %d\n", read_cnt);
      send_cnt = write(cl_fd, buf, read_cnt);
      printf("send_cnt %d\n", send_cnt);

    }

  }
}
