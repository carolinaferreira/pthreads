// gcc execucaoparalela.c  -o execucaoparalela -lpthread
// ./execucaoparalela

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int id;
} thread_arg;

void *thread(void *vargp);

int main(){
  pthread_t tid[2];
  thread_arg a[2];
  int i = 0;
  int n_threads = 2;

  // Crias as n_threads
  for(i = 0; i < n_threads; i++){
    a[i].id = i;
    pthread_create(&(tid[i]), NULL, thread, (void*)&(a[i]));
  }

  // Espera as threads terminarem
  for(i=0; i < n_threads; i++){
    pthread_join(tid[i], NULL);
  }

  pthread_exit((void *)NULL);
}

void *thread(void *vargp){
  int i = 0;
  thread_arg *a = (thread_arg *) vargp;

  printf("Começou a thread %d\n", a->id);
  // Trabalho qualquer
  for(i=0; i < 1000; i++);
  printf("Terminou a thread %d\n ", a->id);

  pthread_exit((void *)NULL);
}
