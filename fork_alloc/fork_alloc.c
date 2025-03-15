#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

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
  int mem_alloc_size = sizeof(int) * 1000;
  int *a = (int *)malloc(mem_alloc_size);
  printf("Allocated memory = %d\n", mem_alloc_size);
  sigset_t *ss;
  sigsuspend(ss);
}
