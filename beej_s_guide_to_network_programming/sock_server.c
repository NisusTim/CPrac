#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("usage: %s <port>\n", argv[0]);
    return 1;
  }
  int port = (int)strtol(argv[1], NULL, 10);

  int sock_fd = 0;
  int sock_fd_client = 0;
  char buff[256] = {};
  char msg[] = {"Hi, this is server.\n"};

  // AF_INET: IPv4
  // SOCK_STREAM: TCP
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    printf("  tcps: Failed to create a socket.\n");
  }

  struct sockaddr_in server_info;
  struct sockaddr_in client_info;
  int addrlen = sizeof(client_info);
  bzero(&server_info, sizeof(server_info));

  server_info.sin_family = PF_INET;
  server_info.sin_addr.s_addr = INADDR_ANY;
  server_info.sin_port = htons(port);
  bind(sock_fd, (struct sockaddr *)&server_info, sizeof(server_info));
  listen(sock_fd, 5);

  while (1) {
    sock_fd_client = accept(sock_fd, (struct sockaddr *)&client_info, &addrlen);
    send(sock_fd_client, msg, sizeof(msg), 0);
    recv(sock_fd_client, buff, sizeof(buff), 0);
    printf("  tcps: recv_msg: %s\n", buff);
  }

  return 0;
}
