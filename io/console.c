#include <stdio.h>
#include <stdbool.h>     // true
#include <stdlib.h>      // exit()
#include <sys/select.h>  // select()
#include <unistd.h>      // read()

#include <string.h>

/*
 * - fd_set to be singleton? or can be multiple?
 * - add or remove while select()?
 * - fd list (one sorted int []) to store and iterate
 * - list with bits flag to mark fd_set and 3 handlers
 * - struct {
 *     int fd;
 *     int set;  // 000 to 111 indicate r,w,e
 *     void *(*rd_event)(void *arg);
 *     void *(*wr_event)(void *arg);
 *     void *(*ex_event)(void *arg);
 *   }
 * - stdin: trim last new line
 */

#define STDIN     0
#define ENABLED   1
#define DISABLED  0
/* config */
#define DEFAULT_TRIM_MODE  ENABLED

int reset_fds(void);
int set_fds(void);
int handle_fds(int err_code);
char *trim_newline(char *str);
int stdin_handler(char *str, int size);
void hello(void);

// fd set
fd_set READ_FDS;
fd_set WRITE_FDS;
fd_set EXCEPT_FDS;
// fd list to store
// fd_set ;
int MAX_FD = 1;

int main(int argc, char *argv[])
{
  int err_code;

  while (true) {

    reset_fds();

    err_code = select(MAX_FD+1, &READ_FDS, &WRITE_FDS, &EXCEPT_FDS, NULL);

    handle_fds(err_code);
  }
}

int reset_fds(void)
{
  FD_ZERO(&READ_FDS);
  //
  FD_SET(STDIN, &READ_FDS);
  FD_ZERO(&WRITE_FDS);
  FD_ZERO(&EXCEPT_FDS);

  return 0;
}

int set_fds(void)
{
}

int handle_fds(int err_code)
{
  switch (err_code) {
    case -1:
      perror("select()");
      exit(err_code);

    case 0:
      exit(err_code);

    default:
      // iterate fd list and handle it
      for (int i = 0; i <= MAX_FD; ++i) {
        if (FD_ISSET(i, &READ_FDS))
          if (i == STDIN) {
            char buff[255];
            int n = read(STDIN, buff, sizeof(buff));
            n = stdin_handler(buff, n);
            printf("  stdin: '%s' (%d)\n", buff, n);
            fflush(stdout);

            if (!strcmp(buff, "k"))
              hello();
          }
        
      }
  }
}

char *trim_newline(char *str)
{
  int size = strlen(str);

  if (str[size-1] == '\n')
    str[size-1] = '\0';

  return str;
}

/*
 * str: 
 * size: num of char of str
 *
 * return: num of char of str
 *
 *          size
 * abc\0       3
 * abc\n\0     4
 */
int stdin_handler(char *str, int size)
{
  static int trim_mode = DEFAULT_TRIM_MODE;
  str[size] = '\0';

  if (!strncmp(str, "trim on", 7) &&
      (str[8] == '\0' || str[8] == '\n'))
    trim_mode = ENABLED;
  else if (!strncmp(str, "trim off", 8) &&
      (str[9] == '\0' || str[9] == '\n'))
    trim_mode = DISABLED;

  if (trim_mode && str[size-1] == '\n') {
    str[size-1] = '\0';
    return size - 1;
  }

  return size;
}

void hello(void)
{
  printf("hello\n");
}
