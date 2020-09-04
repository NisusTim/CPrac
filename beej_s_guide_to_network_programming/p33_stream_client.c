#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_DATA_SIZE  100

// get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in *)sa)->sin_addr);
  else
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
  int rv;
  int num_bytes;
  char buff[MAX_DATA_SIZE];

  int sock_fd;
  struct addrinfo hints;
  struct addrinfo *serv_info;
  struct addrinfo *p;

  char s[INET6_ADDRSTRLEN];
  const char *ip = argv[1];
  const char *port = argv[2];
  const char *cmd = argv[3];

//  if (argc != 2) {
//    fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
//    return 1;
//  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV;

  if ((rv = getaddrinfo(ip, port, &hints, &serv_info)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and connect to the first we can
  for (p = serv_info; p != NULL; p = p->ai_next) {
    if ((sock_fd = socket(p->ai_family, p->ai_socktype, 
                          p->ai_protocol)) == -1) {
      perror("client: socket");
      continue;
    }
    if (connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sock_fd);
      perror("client: connect");
      continue;
    }
    break;
  }

  freeaddrinfo(serv_info);

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }

  inet_ntop(p->ai_family,
            get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));
  printf("client: connecting to %s\n", s);

  if ((num_bytes = recv(sock_fd, buff, MAX_DATA_SIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  buff[num_bytes] = '\0';
  printf("client: received '%s'\n", buff);

  const char *to_send = cmd;
  send(sock_fd, to_send, sizeof(to_send), 0);

  close(sock_fd);

  return 0;
}
