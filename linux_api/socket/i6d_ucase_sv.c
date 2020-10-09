#include "i6d_ucase.h"

int main(int argc, char *argv[])
{
  struct sockaddr_in6 sv_addr, cl_addr;
  int sv_socket;
  ssize_t recv_msize;
  socklen_t sock_len;
  char buff[BUFF_MSIZE];
  char cl_addr_str[INET6_ADDRSTRLEN];

  sv_socket = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sv_socket == -1)
    errExit("socket");

  memset(&sv_addr, 0, sizeof(struct sockaddr_in6));
  sv_addr.sin6_family = AF_INET6;
  sv_addr.sin6_addr = in6addr_any;
  sv_addr.sin6_port = htons(PORT_NUM);

  if (bind(sv_socket, (struct sockaddr *)&sv_addr, 
           sizeof(struct sockaddr_in6)) == -1)
    errExit("bind");

  /* Receive messages, convert to uppercase, and return to client */

  for (;;) {
    sock_len = sizeof(struct sockaddr_in6);
    recv_msize = recvfrom(sv_socket, buff, BUFF_MSIZE, 0,
                          (struct sockaddr *)&cl_addr, &sock_len);
    if (recv_msize == -1)
      errExit("recvfrom");

    if (inet_ntop(AF_INET6, &cl_addr.sin6_addr, cl_addr_str,  \
                  INET6_ADDRSTRLEN) == NULL)
      printf("Couldn't convert client address to string\n");
    else
      printf("Server received %ld bytes from (%s, %u)\n",  \
             (long)recv_msize, cl_addr_str, ntohs(cl_addr.sin6_port));

    for (int j = 0; j < recv_msize; ++j)
      buff[j] = toupper((unsigned char )buff[j]);

    if (sendto(sv_socket, buff, recv_msize, 0,  \
               (struct sockaddr *)&cl_addr, sock_len) != recv_msize)
      fatal("sendto");
  }

}
