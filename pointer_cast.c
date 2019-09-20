#include <stdio.h>

typedef struct {
  /*int integer = 0;*/
  int data[4096];
  int data_2[8][65];
} s, *s_p;

int main(void) {
  int workspace[8192];
  for (int i = 0; i < 8192; ++i)
    workspace[i] = i;
  s_p point = (s_p)workspace;

  /*for (int i = 0; i < 4096; ++i)*/
    /*printf("%5d", point->data[i]);*/
  printf("%d", point->data[10]);
}
