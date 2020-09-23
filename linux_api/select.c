#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define STDIN           0
#define SOCKET_ERROR  (-1)
#define BACKLOG         5

int tcp_server(short port, int backlog);
int tcp_server_accept(int server_socket);
int check(int exp, const char *msg);

int main(int argc, char *argv[])
{
  int port;
  int sv_socket;
  int cl_socket;
  fd_set current, ready;
  int max_socket_so_far;
  int err_code;

  port = strtol(argv[1], NULL, 10);
  sv_socket = tcp_server(port, BACKLOG);

  FD_ZERO(&current);
  FD_SET(STDIN, &current);
  FD_SET(sv_socket, &current);
  max_socket_so_far = sv_socket;
  printf("sv_socket %d\n", sv_socket);
  cl_socket = 0;

  while (true) {

    ready = current;
    err_code = select(max_socket_so_far+1, &ready, NULL, NULL, NULL);
    check(err_code, "Select error.");

    for (int i = 0; i <= max_socket_so_far; ++i) {
      if (FD_ISSET(i, &ready)) {
        if (i == sv_socket) {

          // accept new connection
          cl_socket = tcp_server_accept(sv_socket);
          FD_SET(cl_socket, &current);
          if (cl_socket > max_socket_so_far)
            max_socket_so_far = cl_socket;

          printf("accept new connection fd-%d\n", cl_socket);

        } else if (i == STDIN) {

          char buff[255];
          /*fgets(buff, sizeof(buff), stdin);*/
          read(STDIN, buff, sizeof(buff));
          send(cl_socket, buff, strlen(buff), 0);

        } else {

          char buff[255];
          int nread;
          nread = recv(cl_socket, buff, sizeof(buff), 0);
          check(nread, "Recv error.");
          /*FD_CLR(i, &current);*/

          printf("recv new msg: '%s' from fd-%d\n", buff, cl_socket);
        }
      }
    }  // for each socket
  }  // while (true)

  return 0;
}

int tcp_server(short port, int backlog)
{
  int server_socket;
  int err_code;
  struct sockaddr_in server_addr;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  check(server_socket, "Failed to create socket.");

  // initialize the address struct
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  err_code = bind(server_socket, (struct sockaddr *)&server_addr, 
                  sizeof(server_addr)); 
  check(err_code, "Bind failed.");
  err_code = listen(server_socket, backlog);
  check(err_code, "Listen failed.");

  return server_socket;
}

int tcp_server_accept(int server_socket)
{
  int client_socket;
  int addr_size;
  struct sockaddr_in client_addr;

  addr_size = sizeof(struct sockaddr_in);
  client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                         (socklen_t *)&addr_size);
  check(client_socket, "Accept failed.");

  return client_socket;
}

int check(int exp, const char *msg)
{
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(1);
  }

  return exp;
}
