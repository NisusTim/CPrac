#include <stdio.h>

typedef void (*CallBack)(void *);

typedef struct _Object {
  CallBack cb;
} obj_t;

void Func_A(void *p)
{
  char *str = (char *)p;
  printf("Here is Func 'A'\n");
}

void Func_B(void *p)
{
  char *str = (char *)p;
  printf("Here is Func 'B'\n");
}

void RegCallBack(obj_t *obj, CallBack cb)
{
  obj->cb = cb;
  printf("obj->cb addr.: %p\n", obj->cb);
}

void ObjectCall(obj_t *obj)
{
  obj->cb("Callback function test..\n");
}

int main(void)
{
  obj_t obj_A, obj_B;
  RegCallBack(&obj_A, Func_A);
  RegCallBack(&obj_B, Func_B);

  int sel;
  do {
    printf("Please enter an integer to call friend\n 1) obj_A   2) obj_B\n");
    scanf("%d", &sel);
    switch (sel) {
    case 1:
      ObjectCall(&obj_A);
      break;
    case 2:
      ObjectCall(&obj_B);
      break;
    default:
      printf("Person NOT found");
      break;
    }
  } while (sel < 3);
}
