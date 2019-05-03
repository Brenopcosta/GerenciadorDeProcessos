#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Processo.h"
#include "executadorProcessador.c"

void main() {
  int numeroDeProcessosRestando = NUMERO_DE_PROCESSOS;
  int numeroDeProcessos = NUMERO_DE_PROCESSOS;
  criaFilaProcessosProntos();
  int tempoDoGerenciador = inicializaProcesso();
  while (numeroDeProcessosRestando > 0) {
    numeroDeProcessosRestando = executaProcesso(numeroDeProcessosRestando, tempoDoGerenciador);
  }
}
