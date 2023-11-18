#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>   // errno != ECHILD

// The memory is copied over to the new process, and the new process has the same values as the parent process had when it forked
int main(int argc, char* argv[]){
	int id1 = fork();
    int id2 = fork();

    // printf("%d %d\n",id1, id2);
	
    if(id1 == 0){
        if(id2 == 0){
            printf("We are process Y\n"); // Level 2
        } else {
            printf("We are oricess X\n"); // Level 1
        }
    } else{
        if(id2 == 0){
            printf("We are process Z\n"); // Level 1
        } else{
            printf("We are the parent process\n"); // Level 0
        }
    }

    // wait(NULL); just waits for ONE process to finish (whichever finished first), so the problem of zombies process will continue
    // Solution:
    while(wait(NULL) != -1 || errno != ECHILD){ // While we were wainting for something. (When equals -1 then we are not waiting for anything)
        // errno != ECHILD to avoid some errors wait(NULL) might produce
        printf("Waited for a child to finish\n");
    }
    return 0;
}