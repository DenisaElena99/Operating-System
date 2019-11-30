#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>

int main (int argc, const char *argv[]) {

	int n=atoi (argv[1]);
	pid_t pid = fork();
	if (pid < 0){
		return errno;
	}
	else{
		if (pid == 0){
			printf("%d:",n);
			while(n!=1){
				printf("%d ",n);
				if (n%2==0){
					n=n/2;
				}
				else{
					n=n*3+1;
				}
			}
			printf("1\n");
		}
		else{
			wait(NULL);
			printf(" Child %d ended\n", pid);
		}
	}



	return 0;
}
