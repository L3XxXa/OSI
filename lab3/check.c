#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){uid_t* uid; printf("UID == %ld and EUID == %ld\n", getuid(), geteuid()); printf("Changing setuid to another\n"); setuid(4587); printf("Changed UID == %ld and EUID == %ld \n", getuid(), geteuid()); return 0;}
