#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // used in linux for threads and processes

int main(int argc, char* argv[]){
	int id = fork();
	if(id != 0){ // I just need three processes
		fork();
	}
	
	printf("Hello world\n");

	return 0;
}