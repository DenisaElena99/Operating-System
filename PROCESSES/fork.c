#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {
	pid_t pid = fork();
	if (pid < 0){
		return errno;
	}
	else{
		if (pid == 0){
			printf("Parent %d Child %d\n", getppid(), getpid());
			char *argv[] = {"ls", NULL};
			execve("/bin/ls", argv, NULL);
			perror(NULL);
		}
		else
        {
			wait(NULL);
			printf("Last!");
		}
	}
	return 0;
}
