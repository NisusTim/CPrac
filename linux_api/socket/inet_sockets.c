#define _DEFAULT_SOURCE  /* To get NI_MAXHOST and NI_MAXSERV definitions from 
                            <netdb.h> */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "inet_sockets.h"
#include "tlpi_hdr.h"

static int inet_passive_socket(const char *service, int type, 
                               socklen_t *addr_len, Boolean do_listen, int backlog)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sv_fd, st, opt_val;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = type;
  hints.ai_flags = AI_PASSIVE;

  st = getaddrinfo(NULL, service, &hints, &result);
  if (st != 0) {
    errno = ENOSYS;
    return -1;
  }

  /* Walk through returned list until we find an address structure that can be
     used to successfully create and bind a socket */

  opt_val = 1;
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sv_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sv_fd == -1)
      continue;  /* On error, try next address */

    if (do_listen) {
      if (setsockopt(sv_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, 
                     sizeof(opt_val)) == -1) {
        close(sv_fd);
        freeaddrinfo(result);
        return -1;
      }
    }

    if (bind(sv_fd, rp->ai_addr, rp->ai_addrlen) == 0)
      break;  /* Success */

    /* bind() failed: close this socket and try next address */

    close(sv_fd);
  }

  if (rp != NULL && do_listen) {
    if (listen(sv_fd, backlog) == -1) {
      freeaddrinfo(result);
      return -1;
    }
  }

  if (rp != NULL && addr_len != NULL)
    *addr_len = rp->ai_addrlen;  /* Return address structure size */

  freeaddrinfo(result);

  return (rp == NULL) ? -1 : sv_fd;
}

int inet_bind(const char *service, int type, socklen_t *addr_len)
{
  return inet_passive_socket(service, type, addr_len, FALSE, 0);
}

int inet_listen(const char *service, int backlog, socklen_t *addr_len)
{
  return inet_passive_socket(service, SOCK_STREAM, addr_len, TRUE, backlog);
}

int inet_connect(const char *host, const char *service, int type)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sv_fd, st;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;  /* Allows IPv4 or IPv6 */
  hints.ai_socktype = type;

  st = getaddrinfo(host, service, &hints, &result);
  if (st != 0) {
    errno = ENOSYS;
    return -1;
  }

  /* Walk through returned list until we find an address structure that can be
     used to successfully connect a socket */

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sv_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sv_fd == -1)
      continue;  /* On error, try next address */

    if (connect(sv_fd, rp->ai_addr, rp->ai_addrlen) != -1)
      break;  /* Success */

    /* Connect failed: close this socket and try next address */

    close(sv_fd);
  }

  freeaddrinfo(result);

  return (rp == NULL) ? -1 : sv_fd;
}

char *inet_address_str(const struct sockaddr *addr, socklen_t addr_len,
                       char *addr_str, int addr_str_len)
{
  char host[NI_MAXHOST], service[NI_MAXSERV];

  if (getnameinfo(addr, addr_len, host, NI_MAXHOST, service, NI_MAXSERV, 
                  NI_NUMERICSERV) == 0)
    snprintf(addr_str, addr_str_len, "(%s, %s)", host, service);
  else
    snprintf(addr_str, addr_str_len, "(?UNKNOWN?)");

  return addr_str;
}

