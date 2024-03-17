#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> // getpid() - getppid()
#include <unistd.h>

// This is another way to avoid zombies processes
int main(int argc, char *argv[]) {
   int id = fork();

   printf("Current ID: %d\n", getpid());   // getpid() returns the process id of the current process
   printf("Parent ID: %d\n", getppid());   // getppid() returns the process id of the parent process
   printf("My child ID: %d\n\n", id);

   // This is going to check if there is any child process to wait for,
   // - if it isn't it's going just return -1,
   // - else will return the id process we are wainting for
   int res = wait(NULL);
   if (res == -1) {
      printf("No children to wait for\n");
   } else {
      printf("%d finished execution\n", res);
   }

   return 0;
}