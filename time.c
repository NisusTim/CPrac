#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
//  time_t start, end;
//  time(&start);
//  usleep(123456);
//  time(&end);
//  printf("%lf sec\n", difftime(end, start));

//  clock_t t = clock();
//  usleep(123456);
//  t = clock() - t;
//  printf("%f sec\n", (float)(t) / CLOCKS_PER_SEC);

  struct timeval t1, t2;
  gettimeofday(&t1, 0);
  usleep(123456);
  gettimeofday(&t2, 0);
  long sec = t2.tv_sec - t1.tv_sec;
  long usec = t2.tv_usec - t1.tv_usec;
  printf("%f sec\n", sec + usec * 10e-6);
}

