#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bloqueadorDeProcessos.h"
#include "finalizadorDeProcessos.h"
#define FATIA_DE_TEMPO

int executaProcesso(int numeroDeProcessos, int tempoDeExecucaoDoGerenciador, int fila[NUMERO_DE_PROCESSOS]) {  
  int i;
  int auxiliar;
  for(i = 0; i < numeroDeProcessos; i++) {
    if (processo[i].pid == fila[0]) {
      break;
    }
  }
  if ((processo[i].tempoDeExecucaoTotal - processo[i].tempoDeExecucaoAtual) > 0) {
    if (strcmp(processo[i].status,"Bloqueado") != 0 && strcmp(processo[i].status,"Finalizado") != 0) {
      while (processo[i].tempoDeTimeSlice < 3 ) {
        processo[i].tempoDeExecucaoAtual++;
        processo[i].tempoDeExecucaoTotal++;
        processo[i].tempoDeTimeSlice++;
        strcpy(processo[i].status,"Executando");
        printf("\n== Processo de PID %d está %s \n", processo[i].pid, processo[i].status);
        printf("Tempo de execucao total do processo: %d\n", processo[i].tempoDeExecucaoAtual);
        printf("Tempo de execução restante: %d ==\n", (processo[i].tempoDeExecucaoTotal - processo[i].tempoDeExecucaoAtual));
      }
      auxiliar = fila[0];
      fila[0] = fila[1];
      fila[1] = auxiliar;      
      strcpy(processo[i].status, "Bloqueado");
      processo[i].tempoDeTimeSlice = 0;
    }
  } else {
    processo[i+1] = processo[i];
    strcpy(processo[i].status, "Finalizado");
    numeroDeProcessos--;
  }
  return numeroDeProcessos;
}
