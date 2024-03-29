#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // open

/*
On Unix, the pipe() function is used to create a pipe between two processes that
are related as a parent and child process, since the pipe is inherited after a
fork(). However, to establish a pipe between two processes that are not directly
related in terms of parent-child hierarchy, other techniques can be used such as
creating named pipes (FIFOs).
*/

// It is not possible to have a pipe between two processes that aren't on the
// same hierarchy, that's why we use FIFOs

// FIFO: a file type to which you can read or write from any process.
int main(int argc, char *argv[]) {
   if(mkfifo("myfifo1", 0777) == -1){ // mkfifo(path, permission bits)
      // If 'myfifo1' already exists the return value will be also -1.
      // To avoid that error we use errno to check if that -1 was due another problem.
      if(errno != EEXIST){
         printf("Could not create fifo file\n");
         return 1;
      }
   }

   /*
   Opening the read or write end of a FIFO blocks until the other end is also
   opened (by another process or thread).

   In other words: If you open a FIFO for writting the open call blocks until
   another process comes along and opens the same FIFO for reading.
   */
   printf("Opening...\n");
   int fd = open("mififo1", O_WRONLY); // Returns the file descriptor
   printf("Opened\n");

   int x = 97;
   if(write(fd, &x, sizeof(x)) == -1){
      return 2;
   }
   printf("Written\n");
   close(fd);
   printf("Closed\n");

   return 0;
}