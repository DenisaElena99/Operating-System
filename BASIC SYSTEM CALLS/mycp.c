#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if( argc < 3) { perror("Introduceti cele doua nume de fisiere"); return -1;}
	int fd1, fd2;
	fd1 = open(argv[1], O_RDONLY|O_CREAT);
	fd2 = open(argv[2], O_WRONLY|O_CREAT, 0644);



	if( fd1 < 0 || fd2 < 0) { perror("Eroare la deschidere"); return errno;}

	const int size = 1024;
	char buff[size];
	ssize_t numRead;
	while((numRead=read(fd1,buff,size))>0)
	{
		if((write(fd2,buff,numRead)) != numRead){ perror("Eroare la scriere"); return errno;}
	}
	if (numRead < 0) { perror("Eroare la citire"); return errno; }
	else if(numRead == 0)
	{
		write(1, "copiere completa/n", 17);
	}

	if(close(fd1) == -1) {perror("Eroare la inchiderea fis1"); return errno;}
	if(close(fd2) == -1) {perror("Eroare la inchiderea fis2"); return errno;}
return 0;
}
