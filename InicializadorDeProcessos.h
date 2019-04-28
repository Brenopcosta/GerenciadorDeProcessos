#include<stdlib.h>
#include<string.h>
#include<time.h>

Processo incializaProcesso(Processo processoDeEntrada)
{
  srand(time(NULL));
  processoDeEntrada.pid = (rand() % 10) + 1;
  processoDeEntrada.tempoDeExecucao = (rand() % 15) + 1;
  strcpy(processoDeEntrada.status, "parado");
  return processoDeEntrada;
}
