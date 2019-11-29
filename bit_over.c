#include <stdio.h>
#include <stdint.h>

struct coord {
  uint8_t x:4;
  uint8_t y:4;
};

int main(void)
{
  struct coord c1 = {0xFF87 & 0xF0, 0xFF87 & 0xF0};
  struct coord c2 = {0xFF87 & 0x0F, 0xFF87 & 0x0F};
  printf("x = %lld,  y = %lld\n", c1.x, c1.y);
  printf("x = %lld,  y = %lld\n", c2.x, c2.y);
  // 0 8
  // 7 0
}
