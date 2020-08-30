#include <netdb.h>      // struct addrinfo, getaddrinfo(), gai_strerror()
#include <arpa/inet.h>  // inet_ntop()
#include <string.h>     // memset()
#include <stdlib.h>     // exit()
#include <stdio.h>      // fprintf()

int main(int argc, char *argv[])
{
  int status;
  char ip_str[INET6_ADDRSTRLEN];
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *p;

  if (argc != 2) {
    fprintf(stderr, "usage: showip <hostname>\n");
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  printf("IP addresses for %s:\n\n", argv[1]);
  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;
    char *ip_ver;

    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ip_ver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ip_ver = "IPv6";
    }
    inet_ntop(p->ai_family, addr, ip_str, sizeof(ip_str));
    printf("  %s: %s\n", ip_ver, ip_str);
  }
  freeaddrinfo(res);

  return 0;
}
