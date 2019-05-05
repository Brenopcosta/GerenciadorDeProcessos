#include <time.h>
#include "fila.c"
#include "Processo.h"


#define NUMERO_DE_PROCESSOS 2
Processo *processo[NUMERO_DE_PROCESSOS];

void inicializaProcesso() {
  srand(time(NULL));
  int i;
  for(i = 0; i < NUMERO_DE_PROCESSOS ;i++) {
    processo[i] = (Processo*) malloc(sizeof(Processo));
    processo[i]->pid = i;
    processo[i]->tempoDeExecucaoTotal = (rand() % 15) + 1;
    processo[i]->tempoDeExecucaoAtual = 0;
    processo[i]->tempoDePedidaDeIO = ((rand() % processo[i]->tempoDeExecucaoTotal)) + 1;
    processo[i]->tipoDeIO = (rand() % 3) + 1;
    processo[i]->tempoDeVoltaDeIO = 500;
    strcpy(processo[i]->status, "Pronto");
    printf("\nDados do processo de PID: %d \n",processo[i]->pid);
    printf("Status da execucao do processo: %s\n",processo[i]->status);
    printd("tempo de pedida de IO %d",processo[i]->tempoDePedidaDeIO);
    printf("Tempo de execucao do processo: %d\n",processo[i]->tempoDeExecucaoTotal );
  }
}

void adicionarProcessosNaFilaDeAltaPrioridade(){
    int i;
    for(i=0; i< NUMERO_DE_PROCESSOS; i++){
      insereElementoNaFila(filaDeAltaPrioridade, processo[i]);
    }
}

void liberaMemoriaAlocadaPorProcesso(){
  int i;
  for(i=0; i < NUMERO_DE_PROCESSOS; i++){
    free(processo[i]);
  }
  puts("\nSucesso");
}
