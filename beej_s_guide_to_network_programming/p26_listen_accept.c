#include <netdb.h>
#include <string.h>

#define MY_PORT   "3490"
#define BACK_LOG  10      // how many pending connections queue will hold

int main(void)
{
  int sock_fd;
  struct addrinfo hints;
  struct addrinfo *res;
  int new_fd;
  socklen_t addr_size;
  struct sockaddr_storage their_addr;

  // don't forget your error checking for these call!!

  // first, load up address structs with getaddrinfo()
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, MY_PORT, &hints, &res);

  // make a socket, bint it, and listen on it
  sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  bind(sock_fd, res->ai_addr, res->ai_addrlen);
  listen(sock_fd, BACK_LOG);

  // accept an incoming connections
  addr_size = sizeof(their_addr);
  new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &addr_size);

  // ready to communicate on socket descriptor new_fd!
}
