// gcc parameterpassing.c  -o parameterpassing -lpthread
// ./parameterpassing

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int i;
  int j;

} thread_arg;

void *thread(void *vargp);

int main(){
  pthread_t tid;
  thread_arg a;

  a.i = 1;
  a.j = 2;
  // 'thread': ponteiro para a estutura previamente alocada que conterá os atributos da thread
  // 'attr': estrutura contendo as opções de criação para a thread(NULL usa os valores padrão)
  // 'start_routine': frunção que será executada pela thread_arg
  // 'arg': argumento recebido pela função
  // pthread_create(thread, attr, start_routine, arg);
  pthread_create(&tid, NULL, thread, (void*)&a);

  // Essa função faz com que a thread que a chamou espere até que a thread passada como parâmetro retorne
  // 'th': thread a ser esperada
  // 'thread_return': valor de retorno da thread
  // pthread_join(th, thread_return);
  pthread_join(tid, NULL);

  // Essa função termina a execução da thread
  // 'retval': valor de retorno da thread
  // pthread_exit(retval)
  pthread_exit((void *) NULL);
}

void *thread(void *vargp){

  //  Converte a estrutura recebida
  thread_arg *a = (thread_arg *) vargp;
  int i = a -> i;
  int j = a -> j;

  printf("Parametros recebidos: %d %d\n", i, j);
  // Essa função termina a execução da thread
  // 'retval': valor de retorno da thread
  // pthread_exit(retval)
  pthread_exit((void *)NULL);
}
