#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
	FILE *fin = fopen("file.txt", "r");
	FILE *fout;
	printf("%d", BUFSIZ);
	char line[BUFSIZ];
	if (fin == (FILE*) NULL){
		perror("Can't open your file");
		exit(1);
	}
	fout = popen("wc -l", "w");
	while (fgets(line, BUFSIZ, fin) != (char*) NULL){
		if(line[0] == '\n'){
			fputs(line, fout);
		}
	}
	fclose(fin);
	pclose(fout);
	return 0;
}
