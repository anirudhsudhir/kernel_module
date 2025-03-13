#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("PID is: %d\n", getpid());
  int *a = (int *)malloc(sizeof(int) * 1000);
  sleep(1000);
  return 0;
}
