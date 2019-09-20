#include <stdio.h>
#include <string.h>

typedef struct type {
  int i;
  float f;
  char c[20][5];
} Type;

Type T1 = {0};
Type T2 = {.c = "Damn", .i = 8, .f = 3.14};
Type *tp1 = &T1;
Type *tp2 = &T2;

int main(void)
{
  /*T2 = {i = 8, f = 3.14};*/
  /*memset(&T1, *(char *)&T2, sizeof(Type));*/
  /*
  memcpy(&T1, &T2, sizeof(Type));
  printf("%d, %f, %s\n", T1.i, T1.f, T1.c);
  printf("%d, %f, %s\n", T2.i, T2.f, T2.c);
  printf("%lu", sizeof(Type));
  */
  for (int i = 0; i < 20; ++i) {
    /*printf("%d", ++x);*/
  }
  memcpy(tp1->c[0], tp2->c[0], sizeof(tp2->c[0]));
  printf("%s\n", tp1->c[0]);
  printf("%s\n", tp1->c[0]);
  return 0;
}
