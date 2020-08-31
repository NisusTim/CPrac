#include <netdb.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
  int sock_fd;
  struct addrinfo hints;
  struct addrinfo *res;

  // first, load up address structs with getaddrinfo();
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;       // use IPv4 or IPv6, whatever
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;       // fill in my IP for me

  getaddrinfo(NULL, "3490", &hints, &res);  // given port number on localhost

  // make a socket
  sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  // bind it to the port we passed in to getaddrinfo()
  bind(sock_fd, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
}
