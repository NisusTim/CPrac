#include "ud_ucase.h"

int main(int argc, char *argv[])
{
  struct sockaddr_un sv_addr, cl_addr;
  int sv_socket;
  size_t msg_msize;
  ssize_t recv_msize;
  char resp[BUFF_MSIZE];

  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s msg...\n", argv[0]);

  /* Create client socket; bind to unique pathname (based on PID) */

  sv_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sv_socket == -1)
    errExit("socket");

  memset(&cl_addr, 0, sizeof(struct sockaddr_un));
  cl_addr.sun_family = AF_UNIX;
  snprintf(cl_addr.sun_path, sizeof(cl_addr.sun_path), 
           "/tmp/ud_ucase_cl.%ld", (long)getpid());

  if (bind(sv_socket, (struct sockaddr *)&cl_addr, 
           sizeof(struct sockaddr_un)) == -1)
    errExit("bind");

  /* Construct address of server */

  memset(&sv_addr, 0, sizeof(struct sockaddr_un));
  sv_addr.sun_family = AF_UNIX;
  strncpy(sv_addr.sun_path, SV_SOCK_PATH, sizeof(sv_addr.sun_path) - 1);

  /* Send messages to server; echo responses on stdout */
  
  for (int j = 1; j < argc; ++j) {
    msg_msize = strlen(argv[j]);  /* May be longer than BUFF_MSIZE */
    if (sendto(sv_socket, argv[j], msg_msize, 0, (struct sockaddr *)&sv_addr, 
               sizeof(struct sockaddr_un)) != msg_msize)
      fatal("sendto");
    recv_msize = recvfrom(sv_socket, resp, BUFF_MSIZE, 0, NULL, NULL);
    if (recv_msize == -1)
      errExit("recvform");
    printf("Response %d: %.*s\n", j, (int)recv_msize, resp);
  }

  remove(cl_addr.sun_path);       /* Remove client socket pathname */
  exit(EXIT_SUCCESS);
}
