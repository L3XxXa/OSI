#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	uid_t uid;
	printf("UID == %ld end EUID == %ld\n", getuid(), geteuid());
	if((fp = fopen("file.txt", "r")) == NULL){
		perror("Can't open this file");
		exit(1);
	}
	else{
		printf("File open was successful\n");
		fclose(fp);
	}
	setuid(uid = getuid());
	printf("uid ==  %ld, euid == %ld\n", getuid(), geteuid());
	if((fp = fopen("file.txt", "r")) == NULL){
		perror("Can't open this file");
		exit(1);
	}
	else{
		printf("File open was successful\n");
		fclose(fp);
	}
	return 0;
}
