#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

int a[100][100];
int b[100][100];
int c[100][100];
int n1,m1,n2,m2;

void *calcul (void *arg) {
	int *rezultat = (int *)malloc(sizeof(int));
	int *argumente = (int *)arg;
	int i=argumente[0];
	int j=argumente[1];
	for(int k=1; k<=m1; k++)
	{
		rezultat[0]+=(a[i][k]*b[k][j]);
	}
	return rezultat;
}

int main ()
{
	scanf("%d %d", &n1, &m1);
	for(int i=1; i<=n1; i++)
		for(int j=1; j<=m1; j++)
			scanf("%d" , &a[i][j]);
	scanf("%d %d" , &n2, &m2);
	for(int i=1; i<=n2; i++)
		for(int j=1; j<=m2; j++)
			scanf("%d" , &b[i][j]);
	int contor=0;
	pthread_t thd[100*100+1];
	for(int i=1; i<=n1; i++)
	{
		for(int j=1; j<=m2; j++)
		{
			int* arg;
			arg =(int *)malloc(2*sizeof(int));
			arg[0]=i;
			arg[1]=j;
			if(pthread_create(&thd[contor], NULL, calcul, arg))
			{
 				perror(NULL);
				return errno;
			}
			contor++;
		}
	}
	contor=0;
	for(int i=1; i<=n1; i++)
	{
		for(int j=1; j<=m2; j++)
		{
			int *result=(int *)malloc(sizeof(int));
			if(pthread_join(thd[contor], &result))
			{
				perror(NULL);
				return errno;
			}
			c[i][j]=*result;
			contor++;
		}
	}
	for(int i=1; i<=n1; i++){
		for(int j=1; j<=m2; j++){
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
	return 0;
}


