#include <netdb.h>      // getaddrinfo(), gai_strerror()
#include <unistd.h>     // close()
#include <arpa/inet.h>  // inet_ntop()
#include <sys/wait.h>   // WNOHANG, waitpid()
#include <signal.h>
#include <errno.h>      // errno
#include <string.h>
#include <stdlib.h>     // exit()
#include <stdio.h>

#define PORT     "3490"  //
#define BACKLOG  10      //

void sigchld_handler(int s)
{
  // waitpid() might overwrite errno, so we save and restore it
  int saved_errno = errno;

  while (waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in *)sa)->sin_addr);
  else 
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
  int rv;
  int yes = 1;
  int sock_fd;
  struct addrinfo hints;
  struct addrinfo *serv_info;
  struct addrinfo *p;

  int new_fd;
  struct sockaddr_storage their_addr;
  socklen_t sin_size = sizeof(their_addr);
  char s[INET6_ADDRSTRLEN];
  struct sigaction sa;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((rv = getaddrinfo(NULL, PORT, &hints, &serv_info)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and bind to the first we can
  for (p = serv_info; p != NULL; p = p->ai_next) {
    if ((sock_fd = socket(p->ai_family, p->ai_socktype, 
                          p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, 
                   sizeof(int)) == -1) {
      perror("setsockopt");
      exit(1);
    }
    if (bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sock_fd);
      perror("server: bind");
      continue;
    }
    break;
  }

  freeaddrinfo(serv_info);

  if (p == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
  }
  if (listen(sock_fd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  sa.sa_handler = sigchld_handler;  // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("server: waiting for connections...\n");
  // main accept() loop
  while (1) {
    new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);

    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    inet_ntop(their_addr.ss_family, 
              get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
    printf("server: got connection from %s\n", s);
    // child process
    if (!fork()) {
      close(sock_fd);  // child doesn't need the listener
      if (send(new_fd, "Hello, world!", 13, 0) == -1)
        perror("send");
      close(new_fd);
      exit(0);
    }
    close(new_fd);  // parent doesn't need this
  }

  return 0;
}
