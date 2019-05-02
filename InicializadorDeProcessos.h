#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMERO_DE_PROCESSOS 2

Processo processo[NUMERO_DE_PROCESSOS];
int fila[NUMERO_DE_PROCESSOS];

int inicializaProcesso() {
  srand(time(NULL));
  int i, tempoDeExecucaoDoGerenciador;
  for(i = 0; i < NUMERO_DE_PROCESSOS ;i++) {
    processo[i].pid = (rand() % 10) + 1;
    processo[i].tempoDeExecucaoTotal = (rand() % 15) + 1;
    processo[i].tempoDeExecucaoAtual = 0;
    processo[i].tempoDeTimeSlice = 0;
    fila[i] = processo[i].pid;
    strcpy(processo[i].status, "Pronto");
    printf("\nDados do processo de PID: %d \n",processo[i].pid);
    printf("Status da execucao do processo: %s\n",processo[i].status);
    printf("Tempo de execucao do processo: %d\n",processo[i].tempoDeExecucaoTotal );
  }
  for(i=0; i<2; i++) {
        tempoDeExecucaoDoGerenciador = tempoDeExecucaoDoGerenciador + processo[i].tempoDeExecucaoTotal;
  }
  return tempoDeExecucaoDoGerenciador;
}
