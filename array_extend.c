#include <stdio.h>
#include <stdint.h>

uint8_t arr[2] = {3, 7};
uint8_t *p1;
uint8_t *p2;
uint8_t arr2d[3][2] = {{0, 1}, {2, 3}, {4, 5}};

int main(void) {
  // 
  p1 = arr;
  printf(" 1. %d\n", *p1);
  p2 = arr2d[0];
  printf(" 2. {%d, %d}\n", p2[0], p2[1]);
}
