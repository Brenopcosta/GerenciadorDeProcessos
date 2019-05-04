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

  while (isGerenciadorLigado) {
      verificaTerminoDeGerenciador();
      verificaFilaDeAltaPrioridade();
      verificarVoltaDeIO();
      if (isRodadaOciosa()){
        tempoDoGerenciador++;
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
