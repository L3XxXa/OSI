#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

char* socket_path = "./socket";

int main(){
	char buff[BUFSIZ];
	int sock, chars;
	struct sockaddr_un addr;
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == -1){
		perror("Not able to make socket");
		exit(-1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		perror("Not able to connect");
		exit(-1);
	}
	printf("KNOCK-KNOCK\n");
	printf("Connected to server\nTo finish abort the connection send CTRL+C\n");
	memset(buff, 0, sizeof(buff));
	while((chars = read(STDIN_FILENO, buff, sizeof(buff))) !=0){
		if (write(sock, buff, chars) != chars){
			if(chars == -1){
				perror("Not able to write");
			}
		}
	}
	printf("Client shutdown\n");
	exit(0);
}
