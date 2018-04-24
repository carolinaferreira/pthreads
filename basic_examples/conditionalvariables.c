#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int id;
} thread_arg;

void *thread(void *vargp);

pthread_mutex_t mutex;
pthread_cond_t cond;

int main(){
  pthread_t tid[2];
  thread_arg a[2];

  int i = 0;
  int n_threads = 2;

  pthread_mutex_init(&mutex, NULL);

  pthread_cond_init(&cond, NULL);


  for(i=0; i < n_threads; i++){
    a[i].id = i;
    pthread_create(&(tid[i]), NULL, thread, (void *)&(a[i]));
  }

  for( i=0; i < n_threads; i++){
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  pthread_exit((void *)NULL);
}

void *thread(void *vargp){
  thread_arg *a = (thread_arg *) vargp;

  if(a->id==0){
    printf("Thread %d: Esperando a outra thread\n", a->id);
    pthread_cond_wait(&cond, &mutex);
    printf("Thread %d: Acabou a espera\n", a->id);
  }else{
    sleep(3);
    printf("Thread %d: Sinalizando a outra thread\n", a->id);
    pthread_cond_signal(&cond);
  }

  pthread_exit((void *)NULL);
}
