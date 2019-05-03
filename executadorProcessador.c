#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "InicializadorDeProcessos.c"
#define FATIA_DE_TEMPO 3

int executaProcesso(int numeroDeProcessos, int tempoDeExecucaoDoGerenciador) {  
  int auxiliar = 0;
  int tempoRestanteDeExecucaoDoProcesso = (filaDeProcessosProntos->inicio->processo.tempoDeExecucaoTotal) - (filaDeProcessosProntos->inicio->processo.tempoDeExecucaoAtual);
  if (tempoRestanteDeExecucaoDoProcesso > 0) {
    //executa o processo
    while (auxiliar < FATIA_DE_TEMPO && filaDeProcessosProntos->inicio->processo.tempoDeExecucaoAtual < filaDeProcessosProntos->inicio->processo.tempoDeExecucaoTotal) {
      auxiliar++; 
      filaDeProcessosProntos->inicio->processo.tempoDeExecucaoAtual++;
      strcpy(filaDeProcessosProntos->inicio->processo.status, "Executando");
      printf("\nProcesso %d está %s no tempo de CPU %d", filaDeProcessosProntos->inicio->processo.pid, filaDeProcessosProntos->inicio->processo.status, filaDeProcessosProntos->inicio->processo.tempoDeExecucaoAtual);
    }
    if ( (filaDeProcessosProntos->inicio->processo.tempoDeExecucaoAtual) == (filaDeProcessosProntos->inicio->processo.tempoDeExecucaoTotal) ) {
      strcpy(filaDeProcessosProntos->inicio->processo.status, "Finalizado");
      printf("\nProcesso %d foi finalizado", filaDeProcessosProntos->inicio->processo.pid);
      removeProcessoDaFila(filaDeProcessosProntos);
      numeroDeProcessos--;
    } else {
      strcpy(filaDeProcessosProntos->inicio->processo.status, "Bloqueado");
      printf("\nO processo %d foi %s e enviado para o final da fila de prontos, o próximo a ser executado será o %d", filaDeProcessosProntos->inicio->processo.pid,
      filaDeProcessosProntos->inicio->processo.status, filaDeProcessosProntos->inicio->proximoElementoDaFila->processo.pid); 
      insereElementoNaFila(filaDeProcessosProntos, filaDeProcessosProntos->inicio->processo);
      removeProcessoDaFila(filaDeProcessosProntos);
    }
  } else {
    strcpy(filaDeProcessosProntos->inicio->processo.status, "Finalizado");
    removeProcessoDaFila(filaDeProcessosProntos);
    numeroDeProcessos--;
  }
  return numeroDeProcessos;
}
