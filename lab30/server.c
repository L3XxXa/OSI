#include <sys/socket.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
char* socket_path = "./socket";

int main(){
	struct sockaddr_un addr;
	int sock, client, chars;
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	char buff[BUFSIZ];
	if (sock == -1){
		perror("Not able to make a socket");
		exit(-1);
	}
	printf("Socket was made successfully\n");
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	unlink(socket_path);
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);


	printf("Binding socket...\n");
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)	{
		perror("Not able to bind a socket");
		exit(-1);
	}
	printf("The socket was binded successfully\nListening...\n");
	if (listen(sock, 1) == -1){
		perror("Not able to listen");
		exit(-1);
	}
	printf("Listened successfully\n");
	printf("Waiting for someone to connect...\n");
	client = accept(sock, NULL, NULL);
	if (client == -1){
		perror("Not able to get socket");
		close(sock);
		exit(-1);
	}
	unlink(socket_path);
	printf("Who is here?\n");
	printf("Waiting for input\n");
	while((chars = read(client, buff, BUFSIZ)) != 0) {
		for(int i = 0; i < chars; ++i){
			putchar(toupper(buff[i]));
		}
	}
	if(chars == 0){
		close(client);
		close(sock);
		printf("Client shutdown\nSocket shutdown\n");
		exit(0);
	}

	if(chars == -1){
		perror("Not able to read");
		exit(-1);
	}
}
