#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define MULTIPLIER_MODULUS 1000

void alloc_sleep();

int main() {
  printf("Parent PID = %d\n", getpid());

  for (int i = 0; i < 3; i++) {
    pid_t child_pid = fork();

    if (child_pid == 0) {
      alloc_sleep();
    } else if (child_pid == -1) {
      printf("Failed to fork successfully\n");
      return 0;
    }
  }

  wait(NULL);
  return 0;
}

void alloc_sleep() {
  printf("\nForked parent to create child with PID = %d\n", getpid());
  size_t multiplier = getpid() % MULTIPLIER_MODULUS;
  size_t mem_alloc_size = sizeof(long) * 1000 * multiplier;
  long *a = (long *)malloc(mem_alloc_size);
  printf("Allocated memory = %ld KB\n", mem_alloc_size / 1024);

  sigset_t s_mask;
  sigemptyset(&s_mask);
  sigsuspend(&s_mask);

  free(a);
  printf("Exiting from child with PID = %d\n", getpid());
}
