#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // inet_addr()
#include <sys/time.h>    // gettimeofday()
#include <pthread.h>

#define BUFF_SIZE  1500
#define RUN        1
#define TO_LOG     0

static void *recv_handler(void *arg);

int main(int argc, char *argv[])
{
  char *ip;
  int sock_fd, port;
  pthread_t tid;

  if (argc < 3) {
    printf("usage: %s <hostname> <port>\n", argv[0]);
    return 1;
  }

  ip = argv[1];
  port = (int)strtol(argv[2], NULL, 10);
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd == -1) {
    printf("  tcpc: Failed to create a socket.");
  }

  struct sockaddr_in info;
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;
  info.sin_addr.s_addr = inet_addr(ip);
  info.sin_port = htons(port);

//  struct timeval timeout;
//  timeout.tv_sec = 3;
//  timeout.tv_usec = 0;
//  if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout,
//                 sizeof(timeout)) < 0)
//    printf("setsockopt failed\n");

  int err = connect(sock_fd, (struct sockaddr *)&info, sizeof(info));
  if (err == -1) {
    printf("  tcpc: Connection error.\n");
  }

  // send a message to server
  pthread_create(&tid, NULL, recv_handler, (void *)&sock_fd);

  for (int i = 3; i < argc; ++i) {
    printf("  tcpc: send msg: %s\n", argv[i]);
    send(sock_fd, argv[i], strlen(argv[i]), 0);  // sizeof will get 8
  }

  pthread_join(tid, NULL);
//    int flag = 1;
//    struct timeval start, end;
    //while (1) {
      //if (flag) {
      //  gettimeofday(&start, 0);
      //  flag = 0;
      //}
      //if (cnt > 0) {
      //}
      //else {
      //  gettimeofday(&end, 0);
      //  printf("  tcpc: recv time spent: %f sec\n", 
      //          end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)*1e-6);
			//}
    //}

  //printf("  tcpc: close socket.\n");
  //close(sock_fd);

  return 0;
}

static void *recv_handler(void *arg)
{
  int fd, cnt;
  char recv_buff[BUFF_SIZE];

  fd = *(int *)arg;
  cnt = 0;

//#if TO_LOG
//  FILE *f = fopen("log.txt", "w");
//  if (f == NULL)
//    printf("  tcpc: log fopen failed.\n");
//#endif

  while (1) {
    printf("  tcpc: wait for recv...\n");
    cnt = recv(fd, recv_buff, sizeof(recv_buff), 0);

    if (cnt == -1) {
      fprintf(stderr, "  tcpc: recv error.");
      exit(1);
    } else if (cnt == 0) {
      break;
    }
      
    recv_buff[cnt] = '\0';
    printf("  tcpc: recv_msg: %s (%d)\n", recv_buff, cnt);

//#if TO_LOG
//    fwrite(recv_buff, sizeof(char), cnt, f);
//#endif
  }
//#if TO_LOG
//  if (f != NULL)
//    fclose(f);
//#endif
  close(fd);

  return NULL;
}
