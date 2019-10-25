#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(void)
{
  char arr[1024] = "abcdefg\0";
  uint64_t addr = (uint64_t) arr;
  char *p = (char *)addr;

  printf("array addr: %p, value: %s\n", arr, arr);
  printf("addr      : %p, value: 0x%lx\n", &addr, addr);
  printf("p         : %p, value: %s\n", p, p);
  printf("0x%04x\n", 0x345);

  char a[] = "0x12345678";
  printf("a: %s, value: 0x%08lX\n", a, strtol(a, NULL, 0));
}

