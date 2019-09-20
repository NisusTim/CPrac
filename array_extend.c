#include <stdio.h>
#include <stdint.h>

/*uint8_t arr[2] = {3, 7};*/
uint8_t *p;
uint8_t *arr;
uint8_t arr2d[3][2] = {{0, 1}, {2, 3}, {4, 5}};

int main(void) {
  /*p = arr;*/
  /*printf("%d", *(p));*/
  arr = arr2d[0];
  printf("{%d, %d}", arr[0], arr[1]);
}
