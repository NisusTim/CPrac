#include <arpa/inet.h>  // htons(), struct sockaddr_in
#include <unistd.h>     // close()
#include <stdio.h>      // perror()
#include <stdlib.h>     // strtol()
#include <string.h>     // memset()
#include "ipv4_sockets.h"
#include "types.h"

#define SOCKET_ERROR  -1
//#define CHECK_SOCKET(err_code, msg)                        \
//  if (err_code == SOCKET_ERROR) { perror(msg); exit(1); }  \
//  return err_code
//#define HANDLE_ERROR(msg)                            \
//  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int ipv4_bind(const char *, int);
int ipv4_listen(const char *, int);
int ipv4_connect(const char *, const char *, int);
static int ipv4_passive_socket(const char *, int, bool, int);


int ipv4_bind(const char *port, int type)
{
  return ipv4_passive_socket(port, type, FALSE, 0);
}

int ipv4_listen(const char *port, int backlog)
{
  return ipv4_passive_socket(port, SOCK_STREAM, TRUE, backlog);
}

int ipv4_connect(const char *ip, const char *port, int type)
{
  struct sockaddr_in sv_addr;
  int sv_socket;

  if ((sv_socket = socket(AF_INET, type, 0)) == SOCKET_ERROR) {
    perror("socket");
    return SOCKET_ERROR;
  }

  memset(&sv_addr, 0, sizeof(struct sockaddr_in));
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = inet_addr(ip);
  sv_addr.sin_port = htons(strtol(port, NULL, 10));

  if (connect(sv_socket, (struct sockaddr *)&sv_addr, 
              sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
    close(sv_socket);
    perror("connect");
    return SOCKET_ERROR;
  }

  return sv_socket;
}

static int ipv4_passive_socket(const char *port, int type, bool do_listen, 
                               int backlog)
{
  struct sockaddr_in sv_addr;
  int sv_socket;
  int reuse;

  if ((sv_socket = socket(AF_INET, type, 0)) == SOCKET_ERROR) {
    perror("socket");
    return SOCKET_ERROR;
  }

  reuse = 1;
  if (do_listen) {
    if (setsockopt(sv_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))
        == SOCKET_ERROR) {
      close(sv_socket);
      perror("setsockopt");
      return SOCKET_ERROR;
    }
  }

  memset(&sv_addr, 0, sizeof(struct sockaddr_in));
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = INADDR_ANY;
  sv_addr.sin_port = htons(strtol(port, NULL, 10));

  if (bind(sv_socket, (struct sockaddr *)&sv_addr, sizeof(struct sockaddr_in))
      == SOCKET_ERROR) {
    close(sv_socket);
    perror("bind");
    return SOCKET_ERROR;
  }

  if (do_listen) {
    if (listen(sv_socket, backlog) == SOCKET_ERROR) {
      // no need to close socket?
      perror("listen");
      return SOCKET_ERROR;
    }
  }

  return sv_socket;
}

