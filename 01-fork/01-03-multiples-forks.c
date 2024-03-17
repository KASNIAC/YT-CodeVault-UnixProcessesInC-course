#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // used in linux for threads and processes

int main(){
   int n;
   scanf("%d", &n);

   int id[n];
   for(int i = 0; i < n; ++i){
      id[i] = fork();
   }

   for(int i = 0; i < n; ++i){
      printf("%d: %d\n",i,id[i]);
   }

   // Draw this to visualize what happens:
   // int id1 = fork();
   // int id2 = fork();
   // int id3 = fork();
   // if(id3 != 0 && id1 == 0){
   //    int id4 = fork();
   // }


}