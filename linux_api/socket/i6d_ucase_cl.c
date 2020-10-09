#include "i6d_ucase.h"

int main(int argc, char *argv[])
{
  struct sockaddr_in6 sv_addr;
  int sv_socket;
  size_t msg_msize;
  ssize_t recv_msize;
  char resp[BUFF_MSIZE];

  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    usageErr("%s host-address msg...\n", argv[0]);

  sv_socket = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sv_socket == -1)
    errExit("socket");

  /* Construct address of server */

  memset(&sv_addr, 0, sizeof(struct sockaddr_in6));
  sv_addr.sin6_family = AF_INET6;
  sv_addr.sin6_port = htons(PORT_NUM);
  if (inet_pton(AF_INET6, argv[1], &sv_addr.sin6_addr) <= 0)
    fatal("inet_pton failed for address '%s'", argv[1]);

  /* Send messages to server; echo responses on stdout */
  
  for (int j = 2; j < argc; ++j) {
    msg_msize = strlen(argv[j]);  /* May be longer than BUFF_MSIZE */
    if (sendto(sv_socket, argv[j], msg_msize, 0, (struct sockaddr *)&sv_addr, 
               sizeof(struct sockaddr_in6)) != msg_msize)
      fatal("sendto");
    recv_msize = recvfrom(sv_socket, resp, BUFF_MSIZE, 0, NULL, NULL);
    if (recv_msize == -1)
      errExit("recvform");
    printf("Response %d: %.*s\n", j-1, (int)recv_msize, resp);
  }

  exit(EXIT_SUCCESS);
}

