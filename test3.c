#include <stdio.h>
#include <stdint.h>

#define kOne 0xFFFF
#define kTwo 0xFFFFFFFF

int main(void)
{
  uint32_t x = 0xFFFF;
  printf("%u", x == (kOne & kTwo));
}
