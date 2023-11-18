#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

// Each process has a copy of its own variables (its own space in memory)
int main(int argc, char* argv[]){
    int id = fork();
    int n;

    if(id == 0){
        n = 1;
    } else{
        wait(NULL);     // We just have to call it in the main process in order to wait the child process finish its work
        n = 6;
    }
    
    for(int i = n; i<n + 5; ++i){
        printf("%d ", i);
        fflush(stdout);     // Flushing the standar output (due the buffer it might wait to print all togheter, that's why we use fflush)
    }

    if(id != 0){
        printf("\n");
    }
    
    return 0;
}