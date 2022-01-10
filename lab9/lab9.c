#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]){
	int status;
	printf("Forking...\n");
	if(fork() == 0){
		printf("Forked successfully\n");
		execvp(argv[1], &argv[1]);
		perror("unable to execute\n");
		exit(1);
	}
	printf("waiting for child\n");
	wait(&status);
	printf("exit status: %d\n", WEXITSTATUS(status));
	exit(0);
}
