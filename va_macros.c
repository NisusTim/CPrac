#include <stdio.h>

#define e1_printf(...)          fprintf(stdout, __VA_ARGS__)
#define e2_printf(args...)      fprintf(stdout, args)
#define e3_printf(format, ...)                   \
  fprintf(stdout, format __VA_OPT__(,) __VA_ARGS__)
#define e4_printf(format, ...)  fprintf(stdout, format, ##__VA_ARGS__)

const char file_name[10] = "file_name";
int line_no = 1;

int main(void)
{
  e1_printf("%s: %d\n", file_name, line_no);
  e1_printf("success!\n");
  e2_printf("%s: %d\n", file_name, line_no);
  e2_printf("success!\n");
  /*e3_printf("%s: %d\n", file_name, line_no);*/
  /*e3_printf("success!\n");*/
  e4_printf("%s: %d\n", file_name, line_no);
  e4_printf("success!\n");
}
