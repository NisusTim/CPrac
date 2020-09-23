#include "us_xfr.h"

#define BACKLOG  5

int main(int argc, char *argv[])
{
  struct sockaddr_un addr;
  int sv_socket, cl_socket;
  ssize_t read_msize;
  char buff[BUFF_SIZE];

  sv_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sv_socket == -1)
    errExit("socket");

  /* Construct server socket address, bind socket to it,
     and make this a listening socket */

  if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
    errExit("remove-%s", SV_SOCK_PATH);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

  if (bind(sv_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_un))
      == -1)
    errExit("bind");

  if (listen(sv_socket, BACKLOG) == -1)
    errExit("listen");

  for (;;) {  /* Handle client connections iteratively */

    /* Accept a connection. The connection is returned on a new
       socket, 'cl_socket'; the listening socket ('sv_socket') remains 
       open and can be used to accept further connections. */

    cl_socket = accept(sv_socket, NULL, NULL);
    if (cl_socket == -1)
      errExit("accept");

    /* Transfer data from connected socket to stdout until EOV */

    while ((read_msize = read(cl_socket, buff, BUFF_SIZE)) > 0)
      if (write(STDOUT_FILENO, buff, read_msize) != read_msize)
        fatal("partial/failed write");

    if (read_msize == -1)
      errExit("read");

    if (close(cl_socket) == -1)
      errMsg("close");
  }
}
