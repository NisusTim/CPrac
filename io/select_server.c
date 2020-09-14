#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>

#define SERVER_PORT     50000
#define SERVER_BACKLOG  5
#define BUFF_SIZE       4096
#define SOCKET_ERROR    (-1)

// prototypes
int setup_server(short port, int backlog);
int accept_new_connection(int server_socket);
void *handle_connection(int);
int check(int exp, const char *msg);

int main(int argc, char *argv[])
{
  int server_socket = setup_server(SERVER_PORT, SERVER_BACKLOG);

  int max_socket_so_far = 0;
  fd_set current_sockets, ready_sockets;

  // initialize my current set
  FD_ZERO(&current_sockets);
  /*FD_ZERO(&ready_sockets);*/
  FD_SET(server_socket, &current_sockets);
  max_socket_so_far = server_socket;

  printf("FD_SETSIZE=%d\n", FD_SETSIZE);
  printf("max_socket_so_far=%d\n", max_socket_so_far);

  while (true) {
    // because select is destructive
    ready_sockets = current_sockets;

    printf("Waiting for connections...\n");
    if (select(max_socket_so_far+1, &ready_sockets, NULL, NULL, NULL) < 0) {
      perror("Select error");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= max_socket_so_far; ++i) {
      if (FD_ISSET(i, &ready_sockets)) {
        if (i == server_socket) {
          // this is a new connection
          int client_socket = accept_new_connection(server_socket);
          FD_SET(client_socket, &current_sockets);
          if (client_socket > max_socket_so_far)
            max_socket_so_far = client_socket;
        } else {
          // do whatever we do with connections
          handle_connection(i);
          FD_CLR(i, &current_sockets);
        }
      }
    }

  }  // while

  return EXIT_SUCCESS;
}

int setup_server(short port, int backlog)
{
  int server_socket, client_socket;
  int addr_size;
  struct sockaddr_in server_addr;

  check(server_socket = socket(AF_INET, SOCK_STREAM, 0), 
        "Failed to create socket");

  // initialize the address struct
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  check(bind(server_socket, (struct sockaddr *)&server_addr, 
             sizeof(server_addr)), "Bind failed");
  check(listen(server_socket, backlog), "Listen failed");

  return server_socket;
}

int accept_new_connection(int server_socket)
{
  int addr_size = sizeof(struct sockaddr_in);
  int client_socket;
  struct sockaddr_in client_addr;

  check(client_socket = 
          accept(server_socket, (struct sockaddr *)&client_addr, 
                 (socklen_t *)&addr_size), "Accept failed");

  return client_socket;
}

void *handle_connection(int client_socket)
{
  char buff[BUFF_SIZE];
  size_t bytes_read;
  int msg_size = 0;
  char actual_path[PATH_MAX+1];

  // read the client's message -- the name of the file to read
  while ((bytes_read = 
            read(client_socket, buff+msg_size, sizeof(buff)-msg_size-1))) {
    msg_size += bytes_read;
    if (msg_size > BUFF_SIZE-1 || buff[msg_size-1] == '\n')
      break;
  }
  check(bytes_read, "Recv_error");
  buff[msg_size-1] = '\0';  // null terminate the message and remove the '\n'

  printf("Request: %s\n", buff);
  fflush(stdout);

  // validity check
  if (realpath(buff, actual_path) == NULL) {
    printf("Error(bad path): %s\n", buff);
    close(client_socket);
    return NULL;
  }

  // read file and send its contensto client
  FILE *fp = fopen(actual_path, "r");
  if (fp == NULL) {
    printf("Error(open): %s\n", buff);
    close(client_socket);
    return NULL;
  }

  // read file contents and send them to client
  // note this is a fine example program, but rather insecure
  // a real program would probably limit the client to certain files
  while ((bytes_read = fread(buff, 1, BUFF_SIZE, fp)) > 0) {
    //printf("Sending %zu bytes\n", bytes_read);
    write(client_socket, buff, bytes_read);
  }
  close(client_socket);
  fclose(fp);
  printf("Closing connection\n");

  return NULL;
}

int check(int exp, const char *msg)
{
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(1);
  }

  return exp;
}
