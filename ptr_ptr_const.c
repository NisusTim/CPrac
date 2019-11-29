#include <stdio.h>

void change_ptr_ptr(const void **ptr);
int x = 0xFF;
int y = 0x00;

int main(void)
{
  int *p;

  printf("x: %p\n", &x);
  printf("y: %p\n", &y);

  p = &x;
  printf("%p\n", p);
  change_ptr_ptr((const void **)&p);
  printf("%p\n", p);
}

void change_ptr_ptr(const void **ptr)
{
  *ptr = &y;
}
