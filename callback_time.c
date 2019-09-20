#include <stdio.h>
#include <stdint.h>

typedef struct {
  uint8_t time;
  void (*callback)(void);
} InfoDisplayed_t;

static InfoDisplayed_t Info;

void HelloWorld(void) 
{
  printf("HelloWorld\n");
}

void CallbackShow(uint8_t time, void (*callback)(void))
{
  Info.time = time;
  Info.callback = callback;

  while (Info.time > 0) {
    --Info.time;
    if (Info.time == 0) {
      if (Info.callback)
        Info.callback();
      Info.callback = 0;
    }
  }
}

void main(void) {
  CallbackShow(10, HelloWorld);
}
