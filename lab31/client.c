#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>

char* socket_path = "./socket";

int main(){
	struct sockaddr_un addr;
	int sock;
	int chars;
	char buff[BUFSIZ];
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == -1){
		perror("Not able to create a socket");
		exit(-1);
	}
	memset(addr.sun_path, 0, sizeof(addr.sun_path));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
	printf("CONNECTING TO THE SERVER...\n");
	if(connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1){
		perror("Not able to connect");
		exit(-1);
	}
	printf("CONNECTED\n TO ABBORT THE CONNECTION SEND CTRL+C\n");
	memset(buff, 0, BUFSIZ);
	while((chars = read(STDIN_FILENO, buff, BUFSIZ)) != 0){
		if(write(sock, buff, chars) != chars){
			if (chars == -1){
				perror("Not able to write");
				exit(-1);
			}
		}
	}
	printf("CLIENT SHUTDOWN\n");
	exit(0);
}
