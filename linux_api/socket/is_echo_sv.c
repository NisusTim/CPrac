#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include "inet_sockets.h"
#include "tlpi_hdr.h"

#define SERVICE    "5000"
#define BUFF_SIZE  4096

/* SIGCHLD handler to reap dead child process */
static void grim_reaper(int sig)
{
  int saved_errno;

  saved_errno = errno;
  while (waitpid(-1, NULL, WNOHANG) > 0 )
    continue;
  errno = saved_errno;
}

static void handle_request(int c_fd)
{
  char buff[BUFF_SIZE];
  ssize_t num_read;

  while ((num_read = read(c_fd, buff, BUFF_SIZE)) > 0) {
    if (write(c_fd, buff, num_read) != num_read) {
      syslog(LOG_ERR, "write() failed: %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (num_read == -1) {
    syslog(LOG_ERR, "Error from read(): %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
  int l_fd, c_fd;
  struct sigaction sa;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = grim_reaper;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    syslog(LOG_ERR, "Error from sigaction(): %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  l_fd = inet_listen(SERVICE, 10, NULL);
  if (l_fd == -1) {
    syslog(LOG_ERR, "Could not create server socket (%s)", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (;;) {
    c_fd = accept(l_fd, NULL, NULL);
    if (c_fd == -1) {
      syslog(LOG_ERR, "Failure in accept(): %s", strerror(errno));
      exit(EXIT_FAILURE);
    }

    switch (fork()) {
      case -1:
        syslog(LOG_ERR, "Can't create child (%s)", strerror(errno));
        close(c_fd);
        break;

      case 0:
        close(l_fd);
        handle_request(c_fd);
        exit(EXIT_SUCCESS);

      default:
        close(c_fd);
        break;
    }
  }
}
