#include <stdio.h>
#include <stdint.h>

int main(void)
{
  uint8_t x = 1;
  uint8_t y = 3;
  uint8_t u = x - y;
  int16_t i = x - y;
  float f = x - y;

  printf(" 1. %u\n", x - y);
  printf(" 2. %u\n", (uint8_t)(x - y));
  printf(" 3. %u\n", u);
  printf(" 4. %d\n", i);
  printf(" 5. %u\n", (uint8_t)i);
  printf(" 6. %f\n", f);
  printf(" 7. %u\n", (uint8_t)f);

  x = 20;
  u = x * 1000 / 240 / 50;
  i = x * 1000 / 240 / 50;
  f = x * 1000 / 240 / 50;

  printf("\n");
  printf(" 8. %u\n", x * 1000 / 240 / 50);
  printf(" 9. %u\n", (uint8_t)(x * 1000 / 240 / 50));
  printf("10. %u\n", u);
  printf("11. %u\n", i);
  printf("12. %u\n", (uint8_t)i);
  printf("13. %f\n", f);
  printf("14. %u\n", (uint8_t)f);

  f = x * 1000.0f / 240 / 50;

  printf("\n");
  printf("15. %f\n", f);
  printf("16. %u\n", (uint8_t)f);

  uint32_t xx = 4287654321U;
  uint32_t uu = xx * 1000 / 240 / 50;
  int64_t  ii = xx * 1000 / 240 / 50;
  float    ff = xx * 1000 / 240 / 50;
  double   dd = xx * 1000 / 240 / 50;

  printf("\n");
  printf("17. %u\n", xx);
  printf("18. %u\n", xx * 1000 / 240 / 50);
  printf("19. %u\n", (uint32_t)(xx * 1000 / 240 / 50));
  printf("20. %u\n", uu);
  printf("21. %lu\n", ii);
  printf("22. %u\n", (uint32_t)ii);
  printf("23. %f\n", ff);
  printf("24. %u\n", (uint32_t)ff);
  printf("25. %lf\n", dd);
  printf("26. %u\n", (uint32_t)dd);

  ff = xx * 1000.0f / 240 / 50;
  dd = xx * 1000.0 / 240 / 50;

  printf("\n");
  printf("27. %f\n", ff);
  printf("28. %u\n", (uint32_t)ff);
  printf("29. %lf\n", dd);
  printf("30. %u\n", (uint32_t)dd);

  uint32_t yy = (uint32_t)(xx * 1000.0 / 240 / 50);
  uint32_t zz = xx * 1000.0 / 240 / 50;

  printf("\n");
  printf("31. %u\n", (uint32_t)(xx * 1000.0 / 240 / 50));
  printf("32. %u\n", yy);
  printf("33. %u\n", zz);

  // conclusion:
  // first, use one double literal to force process of arithmetic operation in 
  // terms of double data type, which gives no loss in precision.
  // second, explicit cast the arithmetic result to integer variable.
  
  int8_t t = -1;
  if (0 > t)
    printf("0ULL > -1");
}
