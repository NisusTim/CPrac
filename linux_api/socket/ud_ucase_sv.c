#include "ud_ucase.h"

int main(int argc, char *argv[])
{
  struct sockaddr_un sv_addr, cl_addr;
  int sv_socket;
  ssize_t recv_msize;
  socklen_t sock_len;
  char buff[BUFF_SIZE];

  sv_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sv_socket == -1)
    errExit("socket");

  /* Construct well-known address and bind server socket to it */
  if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
    errExit("remove-%s", SV_SOCK_PATH);

  memset(&sv_addr, 0, sizeof(struct sockaddr_un));
  sv_addr.sun_family = AF_UNIX;
  strncpy(sv_addr.sun_path, SV_SOCK_PATH, sizeof(sv_addr.sun_path) - 1);

  if (bind(sv_socket, (struct sockaddr *)&sv_addr,  \
           sizeof(struct sockaddr_un)) == -1)
    errExit("bind");

  /* Receive messages, convert to uppercase, and return to client */

  for (;;) {
    sock_len = sizeof(struct sockaddr_un);
    recv_msize = recvfrom(sv_socket, buff, BUFF_SIZE, 0, 
                          (struct sockaddr *)&cl_addr, &sock_len);
    if (recv_msize == -1)
      errExit("recvfrom");

    printf("Server received %ld bytes from %s\n", (long)recv_msize, 
           cl_addr.sun_path);

    for (int j = 0; j < recv_msize; ++j)
      buff[j] = toupper((unsigned char)buff[j]);

    if (sendto(sv_socket, buff, recv_msize, 0, 
               (struct sockaddr *)&cl_addr, sock_len) != recv_msize)
      fatal("sendto");
  }
}
