#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"
#include "InicializadorDeProcessos.h"
#include "executadorProcessador.h"

void main() {
  int nProcessosRestando = NUMERO_DE_PROCESSOS, nProcessos = NUMERO_DE_PROCESSOS;
  int tempoDoGerenciador = inicializaProcesso();
  while (nProcessosRestando > 0) {
    nProcessosRestando = executaProcesso(nProcessosRestando, tempoDoGerenciador, fila);    
  }
}
