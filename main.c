#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"
#include "InicializadorDeProcessos.h"
#include "executadorProcessador.h"

void main() {
  int numeroDeProcessosRestando = NUMERO_DE_PROCESSOS, 
  int numeroDeProcessos = NUMERO_DE_PROCESSOS;
  int tempoDoGerenciador = inicializaProcesso();
  while (numeroDeProcessosRestando > 0) {
    numeroDeProcessosRestando = executaProcesso(numeroDeProcessosRestando, tempoDoGerenciador, fila);    
  }
}
