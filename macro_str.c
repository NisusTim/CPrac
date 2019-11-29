#include <stdio.h>

#define STRINGIFY(x)  #x
#define GREETING      STRINGIFY(cub.tek abc)

int main(void)
{
  printf(GREETING);
}
