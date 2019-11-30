#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
pid_t child_pid;

printf("\nStarting parent %d \n", getpid());

for (int id=1; id<=argc; id++)
{
    child_pid = fork();
    if (child_pid<0)
	{
		return errno;
	}
    if (child_pid == 0)
    {
	int n = atoi(argv[id]);
	printf("%d: ", n);
	while(n!=1)
	{
		if(n%2)
			n = 3*n+1;
		else
			n = n/2;
		printf("%d ", n);
	}
	printf("\nDone Parent %d Me %d\n", getppid(), getpid());
        exit(0);
    }
}

while (wait(NULL) > 0);
	printf("Done Parent %d Me %d\n", getppid(), getpid());
    return 0;
}
