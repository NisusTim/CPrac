#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define SV_SOCK_PATH  "/tmp/ud_ucase"
#define BUFF_SIZE     10  /* Maximum size of messages exchanged between
                             client and server */

/* for build without "error_function.h" header */
#define errExit(format, ...)  printf(format, ##__VA_ARGS__)
#define fatal(format, ...)    printf(format, ##__VA_ARGS__)
#define usageErr(format, ...)   printf(format, ##__VA_ARGS__)
