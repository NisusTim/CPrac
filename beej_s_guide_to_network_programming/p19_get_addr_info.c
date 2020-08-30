#include <netdb.h>   // struct addrinfo, getaddrinfo(), gai_strerror()
#include <string.h>  // memset()
#include <stdlib.h>  // exit()
#include <stdio.h>   // fprintf()

int main(void)
{
  int status;
  struct addrinfo hints;
  struct addrinfo *serv_info;  // to point to result

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;      // no matter IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;      // to auto-fill IP

  if ((status = getaddrinfo(NULL, "3490", &hints, &serv_info)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // serv_info currently points to one or more struct addrinfos of linked-list

  // do something..

  // release linked-list
  freeaddrinfo(serv_info);
}
