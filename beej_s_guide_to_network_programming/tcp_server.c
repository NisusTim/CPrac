#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>  // close()
#include <errno.h>   // errno
#include <string.h>
#include <stdlib.h>  // exit()
#include <stdio.h>

#define DEBUG      1

#define DBGP(...)  do { if (DEBUG) printf(__VA_ARGS__); } while (0)
#define HANDLE_ERROR_EN(en, msg)  \
  do { if (DEBUG) { errno = en; perror(msg); exit(EXIT_FAILURE); } } while (0)

#define STR(x)     #x
#define TCPS_ID    STR(tcps)
#define TCPS       "tcps"

/************************************************
 * Forward Declarations                         *
 ************************************************/
int server_init(int *fd, const char *port, int backlog);
int srv_socket_new(int *fd, const struct addrinfo *srv_info);
void *sockaddr_get(struct sockaddr *sa);
void *srv_connect_handler(void *fd);

void *print_hello(void *arg);
void *countdown(void *arg);

/************************************************
 * Globals                                      *
 ************************************************/
pthread_t TID;

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s <port>", argv[0]);
    return 1;  // error
  }

  char *port = argv[1];
  int listen_fd = 0;
  int accept_fd = 0;
  struct sockaddr_storage acpt_info;
  socklen_t sin_size = sizeof(acpt_info);
  char ip_str[INET6_ADDRSTRLEN];

  if (server_init(&listen_fd, port, 5) != 0) {
    return 2;  // error
  }

  DBGP("  %s: waiting for incoming connections...\n", TCPS);
  pthread_t tid;
  while ((accept_fd = accept(listen_fd, 
                             (struct sockaddr *)&acpt_info, &sin_size))) {
    inet_ntop(acpt_info.ss_family, sockaddr_get((struct sockaddr *)&acpt_info),
              ip_str, sizeof(ip_str));
    DBGP("  %s: connection accept. accept_fd: %d\n", TCPS, accept_fd);
    DBGP("  %s: from %s\n", TCPS, ip_str);

    if (accept_fd < 0) {
      fprintf(stderr, "accept() failed.");
      return 3;  // error
    }
    if (pthread_create(&tid, NULL, srv_connect_handler, (void *)&accept_fd) < 0) {
      fprintf(stderr, "pthread_create() failed.");
      return 4;  // error
    }
  }

  return 0;
}

// return 0: success
int server_init(int *fd, const char *port, int backlog)
{
  struct addrinfo hints = {0};
  struct addrinfo *res;
  int err_code = 0;

  // check input: port

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  
  if ((err_code = getaddrinfo(NULL, port, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err_code));
    return 1;  // error
  }
  if (srv_socket_new(fd, res) != 0) {
    return 2;  // error
  }
  if (listen(*fd, backlog) == -1) {
    return 3;  // error
  } 
  freeaddrinfo(res);

  DBGP("  %s: server_init() done. listen_fd: %d\n", TCPS, *fd);
  return 0;
}

// return 0: success
int srv_socket_new(int *fd, const struct addrinfo *srv)
{
  int yes = 1;

  for (; srv != NULL; srv = srv->ai_next) {
    *fd = socket(srv->ai_family, srv->ai_socktype, srv->ai_protocol);
    if (*fd < 0) {
      continue;
    }
    if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      return 1;  // error
    }
    if (bind(*fd, srv->ai_addr, srv->ai_addrlen) == -1) {
      close(*fd);
      continue;
    }
    break;
  }

  if (srv == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    return 2;  // error
  }

  return 0;
}

void *sockaddr_get(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in *)sa)->sin_addr);
  else
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void *srv_connect_handler(void *fd)
{
  int accept_fd = *(int *)fd;
  char msg[] = "hello world";
  char buff[64];

  send(accept_fd, msg, sizeof(msg), 0);
  recv(accept_fd, buff, sizeof(buff), 0);
  DBGP("  %s: recv msg: %s\n", TCPS, buff);
  close(accept_fd);

  pthread_t tid;

  if (!strcmp(buff, "hello")) {
    pthread_create(&tid, NULL, print_hello, NULL);
  } else if (!strcmp(buff, "cd")) {
    pthread_create(&tid, NULL, countdown, NULL);
    TID = tid;
    printf("  t_id: %lu\n", tid);
  } else if (!strcmp(buff, "stop")) {
    printf("  TID: %lu\n", TID);
    int s = pthread_cancel(TID);
    if (s != 0)
      HANDLE_ERROR_EN(s, "pthread_cancel()");
  } else {
    printf("no this cmd.\n");
  }
}

void *print_hello(void *arg)
{
  printf("hello\n");
}

void *countdown(void *arg)
{
  for (int i = 0; i < 10; ++i) {
    sleep(1);
    printf("  countdown: %d\n", 10-i);
  }
}
