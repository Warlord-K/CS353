#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[]){

	if(argc == 1){
		printf("Please Supply more arguments\n");
		exit(0);
	}
        char arg1 = ' ';
	char arg = '.';
	char file[] = "/snap/bin/code";
	char *ar[2] = {file ,&arg};
	if(*argv[1] == '0'){
		execvp("/usr/bin/firefox", NULL);

	}else if(*argv[1] == '1'){
		execvp("/snap/bin/code", ar);
	}
	return 0;

}