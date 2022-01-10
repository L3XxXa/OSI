#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

int main(){
	int status;
	printf("Forking the process...\n");
	if(fork() == 0){
		printf("The process was forked successfully.\n");
		printf("Executing child process...\n");
		execl("/bin/cat", "cat", "/etc/passwd", (char*) 0);
	}
	printf("Waiting for child process...\n");
	wait(&status);
	printf("Child process exited. Exit code: %d\n", WEXITSTATUS(status));
	exit(0);
}
