#include <stdio.h>
#include <stdint.h>

typedef struct __attribute__ ((packed)) {
  uint8_t x : 1;
  uint8_t y : 2;
  uint8_t z : 4;
  uint8_t a : 3;
  uint8_t b : 6;
} type_t;

typedef struct {
  uint8_t what : 1;
  uint8_t rsvd : 5;
  uint8_t flag : 2;
} type2_t;

int main(void)
{
  type_t t = {.x = 0, .y = 3, .z = 0xF, .a = 7, .b = 0x3F};
  printf("%u, %u, %u, %u, %u\n", t.x, t.y, t.z, t.a, t.b);
  printf("size: %lu\n", (uint64_t)(&t+1) - (uint64_t)&t);

  type2_t t2 = {1, 0, 3};
  printf("%u, %u, %u\n", t2.what, t2.rsvd, t2.flag);
  printf("size: %lu\n", (uint64_t)(&t2+1) - (uint64_t)&t2);
}
