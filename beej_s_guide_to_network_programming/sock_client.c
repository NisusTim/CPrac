#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // inet_addr()

int main(int argc, char *argv[])
{
  int sock_fd = 0;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    printf("  tcpc: Failed to create a socket.");
  }

  struct sockaddr_in info;
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;

  // localhost test
  /*info.sin_addr.s_addr = inet_addr("127.0.0.1");*/
  info.sin_addr.s_addr = inet_addr("192.168.10.200");
  info.sin_port = htons(8700);

  int err = connect(sock_fd, (struct sockaddr *)&info, sizeof(info));
  if (err == -1) {
    printf("  tcpc: Connection error.\n");
  }

  // send a message to server
  char msg[] = {"Hi, there."};
  char recv_msg[256] = {};

  while (1) {
    printf("  tcpc: send_msg: %s\n", msg);
    send(sock_fd, msg, sizeof(msg), 0);
    printf("  tcpc: wait for recv:\n");
    recv(sock_fd, recv_msg, sizeof(recv_msg), 0);
    printf("  tcpc: recv_msg: %s\n", recv_msg);
    sleep(1);
  }
  printf("  tcpc: close socket.\n");
  close(sock_fd);
  return 0;
}
