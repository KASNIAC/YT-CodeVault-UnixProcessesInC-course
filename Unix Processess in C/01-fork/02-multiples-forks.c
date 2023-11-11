#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> // Used in linux for threads and process

int main(int argc, char* argv[]){
	int id = fork();
	if(id != 0){
		fork();
	}
	
	printf("Hello world\n");
	
	return 0;
}
