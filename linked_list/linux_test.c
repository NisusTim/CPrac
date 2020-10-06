#include <stdio.h>
#include <stdint.h>
#include "linux_stddef.h"
#include "linux_kernel.h"

struct my_data {
  int a, b, c;
  struct my_data *next;
};

int main(void) {
  uint8_t x = 0;
  typeof(x) y;
  struct my_data obj;
  struct my_data *ret;
  obj.a = 123;
  obj.b = 456;
  obj.c = 987;
  ret = container_of(&obj.b, struct my_data, b);  // ret = &obj.b

  printf("%u\n", y = 1);
  printf("next: %ld\n", offsetof(struct my_data, next));
  printf("a:    %ld\n", (size_t)&((struct my_data *)0)->a);
  printf("b:    %ld\n", (size_t)&((struct my_data *)0)->b);
  printf("c:    %ld\n", (size_t)&((struct my_data *)0)->c);
  printf("next:    %ld\n", (size_t)&((struct my_data *)0)->next);
  printf("false: %d\n", false);
  printf("ret->a = %d,  ret->b = %d,  ret->c = %d\n", ret->a, ret->b, ret->c);
}
