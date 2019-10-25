#include <stdio.h>

typedef int* int_p;

int main(void) {
  int A = 1;
  int B = 2;
  int C = 3;
  int D = 4;
  int_p a = &A, b, c, d;

  printf("a = %d, %p\n", *a, a);
  printf("b = %d, %p\n", *b, b);
  printf("c = %d, %p\n", *c, c);
  printf("d = %d, %p\n", *d, d);
  (a = b, c, d);
  printf("a = %d, %p\n", *a, a);
  A = 1, 2, 3;
  printf("A = %d\n", A);
  A = (1, 2), 3;
  printf("A = %d\n", A);
  (A = (1, 2)), 3;
  printf("A = %d\n", A);
  A = (1, 2, 3);
  printf("A = %d\n", A);
  /*printf("A = %d\n", (A = 1, 2, 3));*/
  A = 1, B = 2;
}
