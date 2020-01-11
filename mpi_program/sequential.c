#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50000000


int main(int argc, char const *argv[])
{
  clock_t start, end;
  double gap;
  int *a,*b;
  int i=0,sum=0;
  a = (int*)malloc(sizeof(int)*SIZE);
  b = (int*)malloc(sizeof(int)*SIZE);
  for ( i = 0; i < SIZE; i++)
  {
    a[i] = rand() % 100;
    b[i] = rand() % 100;
  }
  start = clock();
  for ( i = 0; i < SIZE; i++)
  {
    sum += a[i] *  b[i];
  }
  end = clock();
  gap = (double)(end - start);
  printf("start: %f end: %f  gap:%f",(double)start, (double)end , gap/ CLOCKS_PER_SEC);
  return 0;
}
