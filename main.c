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
      printf("Rodada %d ........................................................\n",tempoDoGerenciador );
      verificaTerminoDeGerenciador();
      puts("Sucesso na verificação de termino do gerenciador\n");
      verificaFilaDeAltaPrioridade();
      if (!isFilaVazia(filaDeProcessosProntos)){
        printf("FILA DE PRONTOS NAO ESTA VAZIA\n");
      }
      puts("sucesso na verificao da fila de alta prioridade\n");
      verificarVoltaDeIO();
      puts("Sucesso na verificarVoltaDeIO\n");
      if (isRodadaOciosa()){
        tempoDoGerenciador++;
        printf("Rodada Ociosa\n");
        continue;
      }
      puts("Sucesso no isRodadaOciosa\n");
      executaProcesso();
      puts("Sucesso executaProcesso\n");
  }

  liberaMemoriaAlocadaPorProcesso();
  puts("Sucesso\n");
  liberaFila(filaDeAltaPrioridade);
  puts("Sucesso\n");
  liberaFila(filaDeBaixaPrioridade);
  puts("Sucesso\n");
  liberaFila(filaDeProcessosProntos);
  puts("Sucesso\n");
  return 0;
}
