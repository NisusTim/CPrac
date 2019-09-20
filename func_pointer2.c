#include <stdio.h>

int Add(int x, int y)
{
  return x + y;
}

int Mul(int x, int y)
{
  return x * y;
}

int (*func[])(int, int) = {Add, Mul};

int main(void)
{
  printf("%d\n", func[0](3, 4));
  printf("%d\n", func[1](3, 4));
}
