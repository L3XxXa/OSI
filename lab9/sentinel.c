#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]){
	pid_t pid;	
int status;
	for(int i = 0; i < 3; ++i){
		if (fork() == 0){
			printf("FORK BOMB");
			execvp(argv[1], &argv[1]);
			perror("ABOBUS");
		}
	}  

	int n = 3;
	while(n>0){	
		printf("child...");
		pid = 	wait(&status);
		printf("CHILD PID %ld status: %d\n", (long)pid, WEXITSTATUS(status));
		printf("CHILD PID %ld status: %d\n", (long)pid, WEXITSTATUS(status));
	n--;
}
		


}
