#include "us_xfr.h"

int main(int argc, char *argv[])
{
  struct sockaddr_un addr;
  int sv_socket;
  ssize_t read_msize;
  char buff[BUFF_SIZE];

  sv_socket = socket(AF_UNIX, SOCK_STREAM, 0);  /* Create client socket */
  if (sv_socket == -1)
    errExit("socket");

  /* Construct server address, and make the connection */

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  if (connect(sv_socket, (struct sockaddr *)&addr, 
              sizeof(struct sockaddr_un)) == -1)
    errExit("connect");

  /* Copy stdin to socket */

  while ((read_msize = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0)
    if (write(sv_socket, buff, read_msize) != read_msize)
      fatal("partial/failed write");

  if (read_msize == -1)
    errExit("read");

  exit(EXIT_SUCCESS);  /* Close our socket; server sees EOF */
}
