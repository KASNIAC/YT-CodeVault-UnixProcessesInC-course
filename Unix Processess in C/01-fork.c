#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // Used in linux for threads and process

int main(int argc, char* argv[]){
	// id == 0 means that's the child process
	// id != 0 means that's the main process (it refers to the idProcess of his child)
	
	int id = fork(); // returns the process ID
	// fortk(); 	// <- If I had n fork(); I would have 2^n processes
	// If I would like to have 2 processes I just need an if (if the id != 0 then you should be able to split again, otherwise it should'nt do it) (check 02-multiples-forks.c).
	
	// printf("Hello World from id: %d\n", id);
	
	if(id == 0){
		printf("Hello from child process: %d\n", id);
	} else{
		printf("Hello from the main process: %d\n", id);
	}
	
	return 0;
}
