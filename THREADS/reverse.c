#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void *reverse(void *arg)
{
	char *text = arg;
	char *copy = (char*)malloc(strlen(text)+1);
	int len=strlen(text);
	int contor = 0;
	for(int i=len-1; i>=0; i--)
	{
		copy[contor]=text[i];
		contor++;
	}
	return copy;
}

int main(int argc, const char* argv[])
{
	pthread_t thd;
	char *str=argv[1];
	if(pthread_create(&thd, NULL, reverse, str))
	{
		perror(NULL);
		return errno;
	}
	char *result;
	if(pthread_join(thd, &result))
	{
		perror(NULL);
		return errno;
	}
	printf("%s\n", result);
	return 0;
}


