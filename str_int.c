#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ABCD  *(uint32_t *)"abcd"

int main(void)
{
  char     str[] = "abcd";
  uint32_t num   = (uint32_t)*str;

  printf("str: ");
  for (int i = 0; i < 4; ++i)
    printf("0x%X ", str[i]);
  printf("\nnum: 0x%08X\n", num);


  uint32_t num_p  = *(uint32_t *)str;

  printf("num_p: 0x%08X\n", num_p);

  union u {
    char     str[4];
    uint32_t num;
  };

  union u a = {.str = "abcd"};
  union u b = {.num = 0x61626364};
  

  printf("a.str: ");
  for (int i = 0; i < 4; ++i)
    printf("0x%X ", a.str[i]);
  printf("\na.num: 0x%08X\n", a.num);

  printf("b.str: ");
  for (int i = 0; i < 4; ++i)
    printf("0x%X ", b.str[i]);
  printf("\nb.num: 0x%08X\n", b.num);

  printf("0x%08X\n", ABCD);


  printf("0x%02X", "abcd"[0]);
  printf("0x%02X", "abcd"[1]);
  printf("0x%02X", "abcd"[2]);
  printf("0x%02X", "abcd"[3]);


  printf("\n%f\n", (float)strtof("3.14", NULL));
}
