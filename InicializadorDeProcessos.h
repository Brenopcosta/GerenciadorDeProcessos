#include<stdlib.h>
#include<string.h>
#include<time.h>

#define NUMERO_DE_PROCESSOS 2

Processo processo[NUMERO_DE_PROCESSOS];

void incializaProcesso()
{
  srand(time(NULL));
  int i;
  for(i = 0; i < NUMERO_DE_PROCESSOS ;i++){
    processo[i].pid = (rand() % 10) + 1;
    processo[i].tempoDeExecucao = (rand() % 15) + 1;
    strcpy(processo[i].status, "Parado");
  }
}
