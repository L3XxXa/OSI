#include <stdio.h>
#include <stdlib.h>
int main(){
	int randval = rand()%7;
	int randval2 = rand()%7;
	if(randval == randval2){
		printf("PIF-PAF YOU DIED\n");
	}
	else{
		printf("GG\n");
	}
	return 0;
}
