#include <stdio.h>
#include <stdint.h>

#define VarMemInfo(ptr) ({ \
  uint64_t size = (uint64_t)(ptr+1) - (uint64_t)ptr; \
  uint8_t *thru = (uint8_t *)ptr; \
  printf("variable size: %lu\n", size); \
  for (uint64_t i = 0; i < size; ++i) { \
    if (i % 16 == 0) \
      printf("\n"); \
    printf("0x%02X, ", *(thru+i)); \
  } \
  })

typedef struct {
  uint8_t  x;
  uint16_t y;
  uint32_t z;
  int16_t  a;
  int32_t  b;
  int64_t  c;
} type_t;

int main(void)
{
  type_t s = {
    .x = 0x12,
    .y = 0x3456,
    .z = 0x7890ABCD,
    .a = 0xEEFF,
    .b = 0x00112233,
    .c = 0xFEDCBA9876543210};
  VarMemInfo(&s);
}
