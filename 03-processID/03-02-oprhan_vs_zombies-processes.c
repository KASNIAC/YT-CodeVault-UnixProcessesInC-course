#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // getpid() - getppid()

/************************************* Orphan process != Zombie process *************************************

* Zombie process: it has already finished, but the parent has not reviewed its status
  (as long as the parent has not reviewed its status, that information is saved waiting 
  for the parent to check it). The idea is that the parent can know how his son ended up. 
  Technically every process becomes zombie at least for an instant because: The zombie state 
  is the state that occurs after dying but before the parent checks the final state.

* Orphan process: when its parent dies before the son finishes. When a process is orphaned,
  the init process adopts it; When a process adopted by init ends, init immediately checks the
  status of that adopted process that has already finished so that it does not end up as a zombie.

* In general, it is good practice for a parent to take care of his children so that init does not
  have to adopt them.

* If while a process is zombie its parent dies, init adopts it and immediately checks the state of
  its new dead child, so the zombies are released at that moment.


* Summary:

    Situation 1:
    - There's a child process dies
    - He remains a "zombie" because his final state is saved until his parent sees it
    - At the moment in which its parent reviews the final state of the dead child, the information
      of the child process is finally released, not before.

    Situation 2:
    - There's a child process
    - His parent dies
    - The process is orphaned
    - Init adopts it

* The real problem:
    - A process has many children, the children terminate while the parent is still alive but never
      checks the final state of the children, so the children remain zombies until the parent pleases
      to check their status, or until the parent dies to that init comes to save the matter. During all
      this time, the dead children in the zombie state continue to use an entry in the process table,
      which consumes resources.

**************************************************************************************************************/

// Always the child processes should terminate first before the parent process terminates
int main(int argc, char* argv[]){
    int id = fork();

    // In this case we force the parent process to finish first, so the parent of the child process will be reasigned
    // This is considered an orphan process.
    // That's why child process have to finish first than the parent process
    if(id == 0){
        sleep(1); // we wait one second
    }

    printf("Current ID: %d\n", getpid());   // getpid() returns the process id of the current process
    printf("Parent ID: %d\n", getppid());   // getppid() returns the process id of the parent process
    printf("My child ID: %d\n", id);

    // wait(NULL); is usually called at the end of the program to avoid orphan processes

    /*
    // I have to use this in order to wait for the child processes finish their execution
    // By doing this we get the child process execute first and not become an orphan process
    if(id != 0){
        wait(NULL);
    }
    */

    int res = wait(NULL); // This is another way to do it. This is going to check if there is any child process to wait for, 
                          // if it isn't it's going just return -1, otherwhise will return the id process we are wainting for
    if(res == -1){
        printf("No children to wait for\n");
    } else{
        printf("%d finished execution\n", res);
    }

    return 0;
}