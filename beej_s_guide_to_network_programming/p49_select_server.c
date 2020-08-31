#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

//#define PORT           "9034"
#define PORT           "3490"
#define MAX_DATA_SIZE  256

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in *)sa)->sin_addr);
  else
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
  int fd_max;                // maximum file descriptor number
  fd_set master;             // master file descriptor list
  fd_set read_fds;           // temp file descriptor list for socket()

  int listener;              // listening socket descriptor
  int new_fd;                // newly accept() socket descriptor
  struct sockaddr_storage remote_addr;  // client address
  socklen_t addr_len;
  char buff[MAX_DATA_SIZE];  // buffer for client data
  int nbytes;
  char remote_ip[INET6_ADDRSTRLEN];

  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *p;

  int yes = 1;               // for setsockopt() SO_REUSEADDR
  int rv;

  FD_ZERO(&master);          // clear the master and temp sets
  FD_ZERO(&read_fds);

  // get us a socket and bind it
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((rv = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
    fprintf(stderr, "select server: %s\n", gai_strerror(rv));
    exit(1);
  }
  for (p = res; p != NULL; p = p->ai_next) {
    listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (listener < 0) {
      continue;
    }
    // lose the pesky "address already in use" error message
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    
    if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
      close(listener);
      continue;
    }
    break;
  }

  // if we got here, it means we didn't get bound
  if (p == NULL) {
    fprintf(stderr, "select server: failed to bind\n");
    exit(2);
  }

  freeaddrinfo(res);  // all done with this

  // listen
  if (listen(listener, 10) == -1) {
    perror("listen");
    exit(3);
  }
  // add the listener to the master set
  FD_SET(listener, &master);
  // keep track of the biggest file descriptor
  fd_max = listener;  // so far, it's this one

  // main loop
  for (;;) {
    read_fds = master;  // copy it
    if (select(fd_max+1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(4);
    }
    // run through the existing connecitons looking for data to read
    for (int i = 0; i <= fd_max; ++i) {
      if (FD_ISSET(i, &read_fds)) {  // we got one!!
        if (i == listener) {
          // handle new connections
          addr_len = sizeof(remote_addr);
          new_fd = accept(listener, (struct sockaddr *)&remote_addr, &addr_len);
          if (new_fd == -1) {
            perror("accept");
          } else {
            FD_SET(new_fd, &master);  // add to master set
            if (new_fd > fd_max) {    // keep track of the max
              fd_max = new_fd;
            }
            inet_ntop(remote_addr.ss_family, 
                      get_in_addr((struct sockaddr *)&remote_addr),
                                  remote_ip, INET6_ADDRSTRLEN),
            printf("select server: new connection from %s on socket %d",
                   remote_ip, new_fd);
          }
        } else {
          // handle data from a client
          if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
            // got error or connection closed by client
            if (nbytes == 0) {
              // connection closed
              printf("select server: socket %d hung up\n", i);
            } else {
              perror("recv");
            }
            close(i);  // bye!
            FD_CLR(i, &master);  // remove from master set
          } else {
            // we got some data from a client
            for (int j = 0; j <= fd_max; ++j) {
              // send to everyone!
              if (FD_ISSET(j, &master)) {
                // except the listener and ourselves
                if (j != listener && j != i) {
                  if (send(j, buff, nbytes, 0) == -1) {
                    perror("send");
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
