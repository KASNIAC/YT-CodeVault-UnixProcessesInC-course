#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// We want to print numbers from 1 to 10 in order, 1 to 5 with one process and from 6 to 10 with another
int main(int argc, char *argv[]) {
   int id = fork();
   int n; // Each process has a copy of its own variables (its own space in memory)

   if (id == 0) {
      n = 1;
   } else {
      wait(NULL); // We just have to call it in the main process in order to wait the child process finish its work
      n = 6;
   }

   for (int i = n; i < n + 5; ++i) {
      printf("%d ", i);
      fflush(stdout); // Flushing the standar output (due the buffer it might wait to print all togheter, that's why we use fflush)
   }

   if (id != 0) {
      printf("\n");
   }

   return 0;
}

/*
   wait(status_ptr); The argument status_ptr points to a location where wait() can store a status value.
      - This status value is zero if the child process explicitly returns zero status.
      - The status_ptr pointer may also be NULL, in which case wait() ignores the child's return status.
*/