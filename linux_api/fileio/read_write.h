#ifndef READ_WRITE_H_
#define READ_WRITE_H_

#include <sys/types.h>

ssize_t read_line(int fd, void *buffer, size_t msize);
ssize_t read_from(int fd, void *buffer, size_t msize);
ssize_t write_to(int fd, const void *buffer, size_t msize);

#endif  /* READ_WRITE_H_ */
