#include <stdio.h>

int main(void)
{
  int i = 180;
  int j = 180;
  double f = 180.0;
  double h = 180.0;
  
  if (i == h) 
    printf("180 == 180.0\n");
  if (i == (int)h)
    printf("180 == (int)180.0\n");
  h *= 3;
  h /= 3;
  if (i == h)
    printf("180 == 180.0 * 3 / 3\n");
  h *= 3.1415926;
  printf("%f\n", h);
  h /= 3.1415926;
  printf("%f\n", h);
  if (i == h)
    printf("180 == 180.0 * 3.1415926 / 3.1415926\n");

  if (f == j) 
    printf("%.1f == %d\n", f, j);
  if (f == (float)j) 
    printf("%.1f == (float)%d\n", f, j);
  if (f == 180.0) 
    printf("180.0 == 180.0\n");
  if (f == 180.0 * 3 / 3) 
    printf("180.0 == 180.0 * 3 / 3\n");
}
