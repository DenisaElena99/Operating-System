#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
const int n = 5;
int nr;

typedef struct {
  pthread_t thr;
  int id;
}
thread;

thread th[10];///vector de threaduri

int bariera()
{

  pthread_mutex_lock( & mtx);
  nr++;
  pthread_mutex_unlock( & mtx);

  if (nr < n)
{
    if (sem_wait( & sem))
    {
      perror(NULL);
      return errno;
    }
}
  else
{
    for (int i = 0; i < n - 1; i++) {
      if (sem_post( & sem)) {
        perror(NULL);
        return errno;
      }
    }
  }
}

void * tfun(void * v) {

  int id = * (int * ) v;

  printf("%d reached the barrier!\n", id);
  bariera();
  printf("%d passed the barrier!\n", id);

  return NULL;
}

int main() {
  if (pthread_mutex_init( & mtx, NULL)) {
    perror(NULL);
    return errno;
  }

  if (sem_init( & sem, 0, 0)) {
    perror(NULL);
    return errno;
  }

  for (int i = 0; i < n; i++) {
    th[i].id = i;
    pthread_create( & th[i].thr, NULL, tfun, & th[i].id);
  }

  for (int i = 0; i < n; i++) {
    pthread_join(th[i].thr, NULL);
  }

  pthread_mutex_destroy( & mtx);
  sem_destroy( & sem);

  return 0;
}
