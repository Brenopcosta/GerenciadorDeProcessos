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
      verificaTerminoDeGerenciador();
      puts("Sucesso\n");
      verificaFilaDeAltaPrioridade();
      puts("Sucesso\n");
      verificarVoltaDeIO();
      puts("Sucesso\n");
      if (isRodadaOciosa()){
        tempoDoGerenciador++;
        continue;
      }
      puts("Sucesso\n");
      executaProcesso();
      puts("Sucesso\n");
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
