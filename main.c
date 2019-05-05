#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "InicializadorDeProcessos.h"
#include "ControladorGerenciador.h"

int main() {

  criaFilaProcessosProntos();
  criaFilaDeAltaPrioridade();
  criaFilaDeBaixaPrioridade();
  inicializaProcesso();
  adicionarProcessosNaFilaDeAltaPrioridade();

  puts("\n\n\n");
  puts("printando tamanho das filas \n");
  printf("Tamanho da fila de prontos : %d \n",tamanhoFila(filaDeProcessosProntos) );
  printf("Tamanho da fila de ALTA Prioridade : %d \n",tamanhoFila(filaDeAltaPrioridade) );
  printf("Tamanho da fila de BAIXA Prioridade : %d \n",tamanhoFila(filaDeBaixaPrioridade) );
  puts("\n\n\n");

  while (isGerenciadorLigado) {
    puts("\n\n\n");
    puts("printando tamanho das filas \n");
    printf("Tamanho da fila de prontos : %d \n",tamanhoFila(filaDeProcessosProntos) );
    printf("Tamanho da fila de ALTA Prioridade : %d \n",tamanhoFila(filaDeAltaPrioridade) );
    printf("Tamanho da fila de BAIXA Prioridade : %d \n",tamanhoFila(filaDeBaixaPrioridade) );
    puts("\n\n\n");

    if(tempoDoGerenciador == processo[0]->tempoDeExecucaoTotal + processo[1]->tempoDeExecucaoTotal) {
      break;
    }
      if (isTodosOsProcessosTerminados()) {
        break;
      }
      verificarVoltaDeIO();
      verificaFilaDeAltaPrioridade();
      if (isRodadaOciosa()){
        printf("Rodada %d ........................................................\n",tempoDoGerenciador );
        tempoDoGerenciador++;
        printf("Rodado ociosa\n");
        continue;
      }
      executaProcesso();
  }

  liberaMemoriaAlocadaPorProcesso();
  liberaFila(filaDeAltaPrioridade);
  liberaFila(filaDeBaixaPrioridade);
  liberaFila(filaDeProcessosProntos);
  return 0;
}
