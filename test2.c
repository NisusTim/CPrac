#include <stdio.h>
#include <stdint.h>

void (*p)(int8_t);
void (*a)(void);
void P(int8_t);
void A(void);

typedef void (*dummy_a)(void);
typedef void (*dummy_p)(int8_t);

int main(void) 
{
  a = P;
  ((dummy_p)a)(3);
}

void A(void)
{
  printf("Hello!\n");
}

void P(int8_t i)
{
  printf("%d", i);
}
