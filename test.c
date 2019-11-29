#include <stdio.h>
#include <stdint.h>

enum {
  Y = -1,
  X = 0xFFFFFFFF,
};

int main(void)
{
  uint32_t a = X;
  int32_t  b = X;
  uint32_t c = Y;
  int32_t  d = Y;
  printf("a = %lld,  b = %lld\n", a, b);
  printf("c = %lld,  d = %lld\n", c, d);

  uint64_t A = X;
  int64_t  B = X;
  uint64_t C = Y;
  int64_t  D = Y;
  printf("A = %lld,  B = %lld\n", A, B);
  printf("C = %lld,  D = %lld\n", C, D);
}
