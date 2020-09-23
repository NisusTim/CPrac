#include <sys/un.h>
#include <sys/socket.h>
#include "tlpi_hdr.h"

#define SV_SOCK_PATH  "/tmp/us_xfr"
#define BUFF_SIZE      100

/* for build without "error_function.h" header */
#define errExit(format, ...)  printf(format, ##__VA_ARGS__)
#define fatal(format, ...)    printf(format, ##__VA_ARGS__)
#define errMsg(format, ...)   printf(format, ##__VA_ARGS__)
