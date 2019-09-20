#include <stdio.h>

typedef void (*Func_p)(void);

void Hello()
{
  printf("Hello\n");
}

void World()
{
  printf("World\n");
}

Func_p funcs[] = {Hello, World};
// void (*funcs[])(void) = {Hello, World};

int main(void)
{
  int sel;
  Func_p f_p;
  while (1) {
    printf("1) Hello   2) World\n");
    scanf("%d", &sel);
    if (sel > 2)
      break;
    f_p = funcs[sel - 1];
    f_p();
  }
}
