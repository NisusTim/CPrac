#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // inet_addr()
#include <sys/time.h>    // gettimeofday()

int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("usage: %s <hostname> <port>\n", argv[0]);
    return 1;
  }
  char *ip = argv[1];
  int port = (int)strtol(argv[2], NULL, 10);

  int sock_fd = 0;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    printf("  tcpc: Failed to create a socket.");
  }

  struct sockaddr_in info;
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;

  // localhost test
  info.sin_addr.s_addr = inet_addr(ip);
  info.sin_port = htons(port);
  printf("%s: %d\n", ip, port);

  struct timeval timeout;
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;
  if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout,
                 sizeof(timeout)) < 0)
    printf("setsockopt failed\n");


  int err = connect(sock_fd, (struct sockaddr *)&info, sizeof(info));
  if (err == -1) {
    printf("  tcpc: Connection error.\n");
  }

  // send a message to server
  //char msg[] = {"Hi, there."};
  char *msg = argv[3];
  char recv_msg[3000] = {};

  FILE *f = fopen("log.txt", "w");
  if (f == NULL)
    printf("  tcpc: fopen failed.\n");

  int cnt = 0;
  while (1) {
    printf("  tcpc: wait for recv:\n");
    cnt = recv(sock_fd, recv_msg, sizeof(recv_msg), 0);
    printf("  tcpc: recv_msg: %s (%d)\n", recv_msg, cnt);

    if (msg) {
      printf("  tcpc: send_msg: %s\n", msg);
      send(sock_fd, msg, sizeof(msg), 0);
    }

    int flag = 1;
    struct timeval start, end;
    printf("  tcpc: wait for recv:\n");
    while (1) {
      cnt = recv(sock_fd, recv_msg, sizeof(recv_msg), 0);
      if (flag) {
        gettimeofday(&start, 0);
        flag = 0;
      }
      if (cnt > 0) {
        fwrite(recv_msg, sizeof(char), cnt, f);
      }
      else {
        gettimeofday(&end, 0);
        printf("  tcpc: recv time spent: %f sec", 
                end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)*1e-6);
        break;
			}
    }
    break;
  }
  if (f != NULL)
    fclose(f);

  printf("  tcpc: close socket.\n");
  close(sock_fd);
  return 0;
}
