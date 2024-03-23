#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Task: I will have four processes and each one will make a quarter of the sum.
int main(int argc, char *argv[]) {
   int arr[] = {1, 2, 3, 4, 1, 2, 7};
   int arrSize = sizeof(arr) / sizeof(int);

   int start, end;

   int fd1[2];
   int fd2[2];
   int fd3[2];
   if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1) {
      return 1;
   }

   int id1 = fork();
   int id2 = fork();
   if (id1 == -1 || id2 == -1) {
      return 2;
   }

   if(id1 == 0 && id2 == 0){
      start = 0;
      end = arrSize / 4;
   } else if(id1 == 0 && id2 != 0){
      start = arrSize / 4;
      end = arrSize / 2;
   } else if(id1 != 0 && id2 == 0){
      start = arrSize / 2;
      end = (3 * (arrSize)) / 4;
   } else {
      start = (3 * (arrSize)) / 4;
      end = arrSize;
   }

   int sum = 0;
   for (int i = start; i < end; i++) {
      sum += arr[i];
   }

   printf("I'm: %d\nMy parent is: %d\nid1: %d  -  id2: %d\nCalculated partial sum: %d\n\n",getpid(), getppid(), id1, id2, sum);

    // I think it's necessary to close some file descrioptor pipes
   if(id1 == 0 && id2 == 0){
      close(fd1[0]);
      if(write(fd1[1], &sum, sizeof(int)) == -1){
         return 3;
      }
      close(fd1[1]);
   } else if(id1 == 0 && id2 != 0){
      int sumFromChild;
      close(fd1[1]);
      if (read(fd1[0], &sumFromChild, sizeof(int)) == -1) {
         return 4;
      }
      close(fd1[0]);

      int partialSum1 = sum + sumFromChild;

      close(fd2[0]);
      if(write(fd2[1], &partialSum1, sizeof(int)) == -1){
         return 5;
      }
      close(fd2[1]);

      wait(NULL);
   } else if(id1 != 0 && id2 == 0){
      close(fd3[0]);
      if(write(fd3[1], &sum, sizeof(int)) == -1){
         return 6;
      }
      close(fd3[1]);
   } else {
      close(fd2[1]);
      close(fd3[1]);

      int sumFromChild1, sumFromChild2;
      if(read(fd2[0], &sumFromChild1, sizeof(int)) == -1 || read(fd3[0], &sumFromChild2, sizeof(int)) == -1){
         return 7;
      }
      
      close(fd2[0]);
      close(fd3[0]);

      int totalSum = sumFromChild1 + sumFromChild2 + sum;

      printf("Total sum is %d\n", totalSum);
      wait(NULL);
   }

   return 0;
}