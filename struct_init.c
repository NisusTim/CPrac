#include <stdio.h>

typedef struct {
  int a;
  char c;
  float *fp;
} type_s;

int main(void) {
  type_s x = {3};
  printf("a = %d, c = %c, fp = %p", x.a, x.c, x.fp);
}
