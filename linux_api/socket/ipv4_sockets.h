#ifndef IPV4_SOCKETS_H_
#define IPV4_SOCKETS_H_

#include <sys/socket.h>

int ipv4_bind(const char *port, int type);
int ipv4_listen(const char *port, int backlog);
int ipv4_connect(const char *ip, const char *port, int type);

#endif  // IPV4_SOCKETS_H_
