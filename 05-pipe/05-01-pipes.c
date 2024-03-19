#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // write, read, close
#include<sys/wait.h>
#include<errno.h>

// Pipes let us communicate processes. 
// A pipe is an in memory file that only has sort of a buffer that is saved in memory and you can write and read from it
int main(int argc, char* argv[]){
    int fd[2]; // file descriptors for the pipe (a file descriptor is basically a key to access to a file)
    // fd[0] - read
    // fd[1] - write

    // pipe(fd); It's going to save the file descriptors that it opens when we create this pipe
    if (pipe(fd) == -1) {
        printf("An error ocurred with opening the pipe\n");
        return 1;
    }

    int id = fork();
    if(id == -1){
        printf("An error ocurred with fork\n");
        return 4;
    } else if (id == 0) { // I'm the children process
        close(fd[0]); // I'm not going to read nothing from this file
        // It used to be the standar, while a process write, the other read and vice versa

        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1){
            printf("An error ocurred with writing to the pipe\n");
            return 2;
        }

        // tells anybody that might be listening on the other end that this file has been closed and you don't have anything to read from it 
        // (there's no longer any file descriptor that can write to it open)
        close(fd[1]);   
    } else { // I'm the parent process
        close(fd[1]); // I'm not going to write nothing on this file

        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            printf("An error ocurred with reading from the pipe\n");
            return 3;
        }

        close(fd[0]);

        printf("Got from child process: %d\n", y);
    }

    // Since read is a blocking call, wait(NULL) won't be necessary. The parent will wait until the children writes into the pipe.
    return 0;
}