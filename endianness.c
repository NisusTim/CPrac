#include <stdio.h>
#include <stdint.h>

typedef union Endian_32 {
  uint32_t u32;
  uint8_t  c[4];
} Endian_t;

void EndianInfo(Endian_t *edn) {
  printf("uint32    : 0x%08X\n", edn->u32);
  printf("endianness:\n");
  printf("addr.       value\n");
  for (int i = 0; i < 4; ++i)
    printf("%p: 0x%02X\n", &edn->c[i], edn->c[i]);
  printf("\n");
}

void EndianTest(Endian_t *edn) {
  uint8_t *ch = (uint8_t *)&edn->u32;
  uint8_t LSB = (uint8_t)(edn->u32 & 0x000000FF);
  uint8_t MSB = (uint8_t)(edn->u32 >> 24);
  if (*ch == LSB)
    printf("Little-Endian\n");
  else if (*ch == MSB)
    printf("Big-Endian\n");
  else
    printf("Unknown Endian\n");
}

int main(void) 
{
  Endian_t e = {0x12345678};
  EndianTest(&e);
  EndianInfo(&e);
}
