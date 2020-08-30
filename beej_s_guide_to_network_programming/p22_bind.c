#include <netdb.h>
#include <string.h>

int main(void)
{
  int sock_fd;
  struct addrinfo hints;
  struct addrinfo *res;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(NULL, "3490", &hints, &res);

  sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  bind(sock_fd, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
}
