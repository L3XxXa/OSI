#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	FILE* file = popen("./sentinel", "w");
	char* lines[3] = {"It's not an ogre...\n", "Shrek is love...\n", "Shrek is life...\n"};
	for (int i = 0; i<3; ++i){
		fputs(lines[i], file);
	}
	pclose(file);
	return 0;
}
