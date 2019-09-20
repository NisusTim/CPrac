// default size: int size
// $ gcc -o enum_size enum_size.c && ./enum_size
// specify size: char size
// $ gcc -fshort-enums -o enum_size enum_size.c && ./enum_size

#include <stdio.h>

int main(void) {
  enum {
    Mon = 1, Tue, Wed, Thu, Fri, Sat, Sun = 0
  } weekday;
  printf("size of enum: %lu\n", sizeof(weekday));
}
