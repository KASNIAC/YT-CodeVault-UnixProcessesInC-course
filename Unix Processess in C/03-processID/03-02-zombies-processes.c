#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // getpid() - getppid()

// Always the child processes should terminate first before the parent process terminates
int main(int argc, char* argv[]){
    int id = fork();

    // In this case we force the parent process to finish first, so the parent of the child process will be reasigned
    // This is considered a zombie process due if I try to kill it, the memory is not going to actually be freed (memory leak)
    // That's why child process have to finish first than the parent process
    if(id == 0){
        sleep(1); // we wait one second
    }

    printf("Current ID: %d\n", getpid());   // getpid() returns the process id of the current process
    printf("Parent ID: %d\n", getppid());   // getppid() returns the process id of the parent process
    printf("My child ID: %d\n", id);

    // wait(NULL); is usually called at the end of the program to avoid zombies processes

    /*
    // I have to use this in order to wait for the child processes finish their execution
    // By doing this we get the child process execute first and not become a zombie process
    if(id != 0){
        wait(NULL);
    }
    */

    int res = wait(NULL); // This is another way to do it. This is going to check if there is any child process to wait for, if it isn't it's going just return -1, otherwhise will return the id process we are wainting for
    if(res == -1){
        printf("No children to wait for\n");
    } else{
        printf("%d finished execution\n", res);
    }

    return 0;
}