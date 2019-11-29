#include <stdio.h>
#include <stdint.h>

struct date {
  uint8_t month:4;
  uint8_t day  :5;
};

struct event {
  uint8_t name[20];
  struct date date;
};

int main(void)
{
  struct event a = {"event1", {.month = 12, .day = 31}};
  printf("%u-%u", a.date.month, a.date.day);
}
