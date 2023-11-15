#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
int main(int argc, char *argv[]){
	int i;
	printf("Enter Program Id\n");
	scanf("%d", &i);
	bool run = true;
	while(run){
	int f = fork();
	if(f > 0){
	printf("Enter Program Id\n");
	scanf("%d", &i);
	continue;
	}
        char arg1 = ' ';
	char arg = '.';
	char file[] = "/snap/bin/code";
	char *ar[2] = {file ,&arg};
	if(i == 0){
		execvp("/usr/bin/firefox", NULL);

	}else if(i == 1){
		execvp("/snap/bin/code", ar);
	}
	break;
}
	return 0;

}
