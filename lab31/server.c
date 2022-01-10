#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>
#include <poll.h>

#define TRUE 1

int sock = 0;
struct pollfd pfds[10];
char* socket_path = "./socket";


void catchsig(int sig){
	write(STDOUT_FILENO, "\nCLOSING CLIENTS\n", 18);
	unlink(socket_path);
	for(int i = 0; i< 2; ++i){
		close(pfds[i].fd);
	}
	write(STDOUT_FILENO, "CLOSING SOCKET\n", 16);
	close(sock);
	write(STDOUT_FILENO, "GOODBYE!\n", 10);
	exit(0);
}

//char* socket_path = "./socket";
int main(){
	//int sock;
	signal(SIGINT, catchsig);
	char chars;
	int clients = 2;
	char buff[BUFSIZ];
	struct sockaddr_un addr;
	int mgsock;
	fd_set active;
	fd_set fdread;
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	printf("MAKING SOCKET...\n");
	if(sock == -1){
		perror("Not able to make a socket\n");
		exit(-1);
	}
	printf("SOCKET WAS MADE.\n");
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
	unlink(socket_path);
	printf("BINDING SOCKET...\n");
	if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1){
		perror("Not able to bind a socket with addr\n");
		exit(-1);
	}
	printf("SOCKET WAS BINDED.\n");
	if(listen(sock, 5) == -1){
		perror("Not able to listen your socket\n");
		exit(-1);
	}
	int client;
	for(int i = 0; i < clients; ++i){
		printf("Accepting client...\n");
		client = accept(sock, 0, 0);
		if(client == -1){
			perror("Error while accepting");
			continue;
		}
		printf("Connected successfully\n");
		pfds[i].fd = client;
		pfds[i].events = POLLIN;
	}
	int sentinel = clients;
	while(1){
		poll(pfds, clients, -1);
		for(int i = 0; i < clients; ++i){
			if (pfds[i].revents & POLLIN){
				if (read(pfds[i].fd, &chars, 1) != 0){
					putchar(toupper(chars));
				}
				if (chars == -1){
					perror("Not able to read");
					exit(-1);
				}
			}
		}
	}
}

