#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define DINGDONG '\07'

int cnt = 0;
int flag = 0;
void catchsignal(int signal){
	if (signal == SIGQUIT){
		flag = 1;
		return;
	}
	write(STDOUT_FILENO, "\07", sizeof(char));
	cnt++;
}

int main(){
	sigset(SIGINT, catchsignal);
	sigset(SIGQUIT, catchsignal);
	while(1){
		pause();
		if (flag == 1){
			break;
		}
	}
	if (flag == 1){
		printf("\nDINGDONGPEEEEEEEPED %d times\n", cnt);
		exit(0);
	}
	else{
		printf("UNEXPEСTED ERROR\n");
		exit(-1);
	}
}

