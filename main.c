#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "InicializadorDeProcessos.h"
#include "ControladorGerenciador.h"

int main() {

  criaFilaProcessosProntos();
  puts("Sucesso\n");
  criaFilaDeAltaPrioridade();
  puts("Sucesso\n");
  criaFilaDeBaixaPrioridade();
  puts("Sucesso\n");

  inicializaProcesso();
  puts("Sucesso\n");
  adicionarProcessosNaFilaDeAltaPrioridade();
  puts("Sucesso\n");

  while (isGerenciadorLigado) {
    if(tempoDoGerenciador == processo[0]->tempoDeExecucaoTotal + processo[1]->tempoDeExecucaoTotal) {
      break;
    }
      printf("Rodada %d ........................................................\n",tempoDoGerenciador );
      verificaTerminoDeGerenciador();
      verificaFilaDeAltaPrioridade();
      verificarVoltaDeIO();
      if (isRodadaOciosa()){
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
