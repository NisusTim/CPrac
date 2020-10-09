#include <stddef.h>     // NULL
#include <stdio.h>      // perror()
#include <unistd.h>     // ssize_t, read(), write()
#include <errno.h>      // errno
#include "read_write.h"


ssize_t read_line(int fd, void *buffer, size_t msize)
{
  size_t accum_msize = 0;
  ssize_t read_msize;
  char *buff;
  char ch;

  if (buffer == NULL || msize <= 0) {
    errno = EINVAL;
    return -1;
  }

  buff = buffer;                      /* no pointer arithmetic on "void *" */
  for ( ; ; ) {

    read_msize = read(fd, &ch, 1);

    switch (read_msize) {
      case -1:
        if (errno == EINTR)           /* interrupted, restart read() */
          continue;
        else
          return -1;
      case 0:                         /* EOF */
        if (accum_msize == 0)         /* No bytes read; return 0 */
          return 0;
        else                          /* Some bytes read; add '\0' */
          break;
      case 1:
        if (accum_msize < msize-1) {  /* Discard > (msize-1) bytes */
          ++accum_msize;
          *buff++ = ch;
        }
        if (ch == '\n')
          break;
      default:                        /* Impossible */
        break;
    }
  } 

  *buff = '\0';
  return accum_msize;
}

ssize_t read_from(int fd, void *buffer, size_t msize)
{
  size_t accum_msize = 0;
  ssize_t read_msize;
  char *buff;

  if (buffer == NULL || msize <= 0) {
    errno = EINVAL;
    return -1;
  }

  buff = buffer;
  for ( ; ; ) {

    read_msize = read(fd, buff+accum_msize, msize-accum_msize);

    if (read_msize < 0) {          /* error, check errno */
      if (errno == EINTR) {
        /*DBGP("interrupted.. restart read.\n");*/
        continue;
      } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        /*DBGP("client not ready, try again later.\n");*/
        break;
      }
    } else if (read_msize == 0) {  /* EOF: disconnected */
      /*DBGP("read size: 0, try again later.\n");*/
      close(fd);
      break;
    } else if (read_msize > 0) {   /* read */
      accum_msize += read_msize;
      /*DBGP("read size: %d  total: %d\n", read_msize, accum_msize);*/
      if (accum_msize > msize) {
        /*DBGP("buff full.\n");*/
        break;
      } else if (accum_msize < msize) {
        /*DBGP("end of read.\n");*/
        break;
      }
    } else {
      perror("read()");
      return -1;
    }

  }

  return accum_msize;
}

ssize_t write_to(int fd, const void *buffer, size_t msize)
{
  size_t accum_msize = 0;
  ssize_t write_msize;
  const char *msg;

  if (buffer == NULL || msize <= 0) {
    errno = EINVAL;
    return -1;
  }

  msg = buffer;

  for ( ; ; ) {

    write_msize = write(fd, msg-accum_msize, msize-accum_msize);

    if (write_msize < 0) {          /* error, check errno */
      if (errno == EINTR) {
        /*DBGP("interrupted.. restart write.\n");*/
        continue;
      } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
        /*DBGP("client not ready, try again later.\n");*/
        break;
      }
    } else if (write_msize == 0) {  /* EOF: disconnected */
      /*DBGP("write size: 0, try again later.\n");*/
      close(fd);
      break;
    } else if (write_msize > 0) {   /* written */
      accum_msize += write_msize;
      /*DBGP("write size: %d  total: %d\n", write_msize, accum_msize);*/
      if (accum_msize == msize)
        break;
    } else {
      perror("write()");
      return -1;
    }

  }

  return accum_msize;
}

