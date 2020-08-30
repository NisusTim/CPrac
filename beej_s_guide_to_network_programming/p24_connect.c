#include <netdb.h>
#include <stdio.h>

int main(void)
{
  int sock_fd;
  struct addrinfo hints = {0};
  struct addrinfo *res;

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo("www.google.com.tw", "2003", &hints, &res);
  sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  connect(sock_fd, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
}
