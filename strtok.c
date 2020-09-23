#include <stdio.h>
#include <string.h>


int main(void)
{
  /*char msg[] = "mod arg1 arg2";*/
  char msg[] = "";
  char *p = msg;
  int argc;
  char *argv[10];
  
  while ((p = strtok(p, " ")) != NULL) {
    argv[argc++] = p;
    p = NULL;
  }

  for (int i = 0; i < argc; ++i)
    printf("%s\n", argv[i]);
  printf("argc: %d\n", argc);
}
