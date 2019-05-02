#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMERO_DE_PROCESSOS 2

Processo processo[NUMERO_DE_PROCESSOS];

void inicializaProcesso() {
  srand(time(NULL));
  int i;
  for(i = 0; i < NUMERO_DE_PROCESSOS ;i++) {
    processo[i].pid = (rand() % 10) + 1;
    processo[i].tempoDeExecucaoTotal = (rand() % 15) + 1;
    processo[i].tempoDeExecucaoAtual = 0;
    strcpy(processo[i].status, "Pronto");
    printf("\nDados do processo de PID: %d \n",processo[i].pid);
    printf("Status da execucao do processo: %s\n",processo[i].status);
    printf("Tempo de execucao do processo: %d\n",processo[i].tempoDeExecucaoTotal );
  }
}
