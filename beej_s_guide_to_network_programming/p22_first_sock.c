#include <netdb.h>

int main(void)
{
  int sock_fd;
  struct addrinfo hints = {0};
  struct addrinfo *res;

  // query hostname
  // pretend we already filled out the "hints" struct
  getaddrinfo("www.google.com.tw", "http", &hints, &res);

  // error-checking on getaddrinfo should be done
  // and walk the res linked list
  sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  freeaddrinfo(res);
}

