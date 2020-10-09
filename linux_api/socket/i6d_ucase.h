#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define BUFF_MSIZE  10  /* Maximum size of messages exchanged between 
                           client and server */
#define PORT_NUM    50002  /* Server port number */

/* for build without "error_function.h" header */
#define errExit(format, ...)  printf(format, ##__VA_ARGS__)
#define fatal(format, ...)    printf(format, ##__VA_ARGS__)
#define usageErr(format, ...)   printf(format, ##__VA_ARGS__)
