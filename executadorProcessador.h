#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bloqueadorDeProcessos.h"
#include "finalizadorDeProcessos.h"
#define FATIA_DE_TEMPO

int i, tempoDeExecucaoDoGerenciador = 0;
int nProcessos = NUMERO_DE_PROCESSOS;

void executaProcesso() {
    for(i=0; i<2; i++) {
        tempoDeExecucaoDoGerenciador = tempoDeExecucaoDoGerenciador + processo[i].tempoDeExecucaoTotal;
    }

  while (tempoDeExecucaoDoGerenciador > 0 && nProcessos > 0) {
      for(i=0;i<2;i++) {
        while (processo[i].tempoDeExecucaoTotal > 0 ) {
          if ((processo[i].tempoDeExecucaoTotal - 1) == 0 && processo[i].status != "Finalizado" ){
            finalizaProcesso(i);
            nProcessos--;
          }
          if (!strcmp(processo[i].status,"Executando") || !strcmp(processo[i].status,"Pronto") ) {
            processo[i].tempoDeExecucaoTotal--;
            processo[i].tempoDeExecucaoAtual++;
            strcpy(processo[i].status, "Executando");
            printf("\n== Processo de PID: %d está %s \n", processo[i].pid, processo[i].status);
            printf("Tempo restante de execucao: %d ==\n", processo[i].tempoDeExecucaoTotal);
            printf("Tempo atual de execucao: %d ==\n", processo[i].tempoDeExecucaoAtual);
            if (processo[i].tempoDeExecucaoAtual >= 3) {bloqueiaProcesso(i);}
          }
        }
        tempoDeExecucaoDoGerenciador--;
    }
  }
}
