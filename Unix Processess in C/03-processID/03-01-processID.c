#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // getpid() - getppid()

// The process with id = 0 launches everything else in Unix
int main(int argc, char* argv[]){
   int id = fork();

   printf("Current ID: %d\n", getpid());   // getpid() returns the process id of the current process
   printf("Parent ID: %d\n", getppid());   // getppid() returns the process id of the parent process
   printf("My child ID: %d\n\n", id);

   return 0;
}