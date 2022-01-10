#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	char input[1000];
	int s = 0;
	while ((s = read(0, input, sizeof(input))) > 0) {
		for (int i = 0; i < s; ++i){
			input[i] = toupper(input[i]);
			write(1, input, s);
			printf("\n");
		}
	}
	exit(0);
}
