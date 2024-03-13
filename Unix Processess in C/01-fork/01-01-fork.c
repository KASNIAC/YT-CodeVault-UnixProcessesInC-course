#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // used in linux for threads and processes

int main(int argc, char* argv[]){
	// id == 0 means that you are in the child process (id refers you're the child process and that's why id equals 0 on that branch of execution)
	// id != 0 means that you are in the main process (id refers to the idProcess of your child)
	
	int id = fork(); // returns the process ID of the child (that's why the id == 0 when you are in a child process that doesn't create a new child)
	// fork(); 	  // in general, If I had 'n' forks I would have 2^n processes
	// if I would like to have 3 processes I just need an if (if the id != 0 then you should be able to split again, otherwise it should'nt do it) (check 02-multiples-forks.c)
	
	// printf("Hello World from id: %d\n", id);
	
	if(id == 0){
		printf("Hello from child process: %d\n", id);
	} else{
		printf("Hello from the main process: %d\n", id);
	}
	
	return 0;
}