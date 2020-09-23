#include <sys/epoll.h>  // epoll_create1(), epoll_ctl(), struct epoll_event
#include <unistd.h>     // close()
#include <stdio.h>      // fprintf()
#include <string.h>     // strcmp()

#define MAX_EVENTS  5
#define READ_SIZE   10

int main(int argc, char *argv[])
{
  int running = 1;
  size_t bytes_read;
  char read_buffer[READ_SIZE + 1];

  int event_count;
  struct epoll_event event;
  struct epoll_event events[MAX_EVENTS];
  int epoll_fd = epoll_create1(0);

  if (epoll_fd == -1) {
    fprintf(stderr, "failed to create epoll fd.\n");
    return 1;
  }

  event.events = EPOLLIN;
  event.data.fd = 0;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) {
    fprintf(stderr, "failed to add fd to epoll\n");
    close(epoll_fd);
    return 1;
  }

  while (running) {
    printf("\npolling for input...\n");
    event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    printf("%d read events\n", event_count);

    for (int i = 0; i < event_count; ++i) {
      printf("reading fd-%d: ", events[i].data.fd);
      bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
      printf("%zd bytes read.\n", bytes_read);
      read_buffer[bytes_read] = '\0';
      printf("read '%s'\n", read_buffer);

      if (!strncmp(read_buffer, "stop\n", 5))
        running = 0;
    }
  }

  if (close(epoll_fd)) {
    fprintf(stderr, "failed to close epoll fd.\n");
    return 1;
  }

  return 0;
}
