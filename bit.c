#include <stdio.h>
#include <stdint.h>

#define PAGE_SZ  0x20

typedef struct _PageFlag {
  uint8_t head:1;
  uint8_t state:3;
  uint8_t r:4;
} page_flag_t;

/*typedef struct __attribute__ ((packed, aligned(2))) _Page {*/
typedef struct __attribute__ ((packed)) _Page {
/*typedef struct _Page {*/
  uint16_t rel_time;
  page_flag_t flag;
  uint8_t  reserved[29];
} page_t;

typedef struct _Recorder {
  page_flag_t flag;
  uint8_t     CubTek_ID[7];
  uint32_t    timestamp;
  uint16_t    counter;
  uint8_t     reserved[18];
} rec_t;

int main(void)
{
  printf("%lu\n", sizeof(page_flag_t));
  printf("%lu\n", sizeof(page_t));
  //printf("%lu\n", sizeof(((page_t *)0)->flag));
  //printf("%lu\n", sizeof(((page_t *)0)->rel_time));
  //printf("%lu\n", sizeof(((page_t *)0)->reserved));
  //printf("%lu\n", sizeof(page2_t));
  //printf("%lu\n", sizeof(((page2_t *)0)->flag));
  //printf("%lu\n", sizeof(((page2_t *)0)->rel_time));
  //printf("%lu\n", sizeof(((page2_t *)0)->reserved));
  /*printf("%lu\n", sizeof(((rec_t *)0)->reserved));*/
  printf("%lu\n", sizeof(rec_t));
}

// conclusion:
// memory aligned size is determined by the largest size of element in struct
