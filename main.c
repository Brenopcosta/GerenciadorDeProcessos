#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Processo.h"
#include"InicializadorDeProcessos.h"

int tempoDeExecucaoDoGerenciador;


void main()
{
  Processo processo;
  processo = incializaProcesso(processo);

  printf("Dados do processo de PID : %d \n",processo.pid);
  printf("Status da execucao do processo :%s\n",processo.status);
  printf("Tempo de execucao do processo : %d\n",processo.tempoDeExecucao );
  puts("\n\n\n");


  tempoDeExecucaoDoGerenciador = processo.tempoDeExecucao + 1;

  while (tempoDeExecucaoDoGerenciador > 0) {
      if (processo.tempoDeExecucao == 0) {
        printf("Processo de PID : %d finalizado \n", processo.pid );
        break;
      }
      printf(" Processo de PID: %d executando \n", processo.pid);
      printf("Tempo restante de execucao: %d \n", processo.tempoDeExecucao);
      printf("Status do processo : %s\n", processo.status);

      processo.tempoDeExecucao--;
      tempoDeExecucaoDoGerenciador--;
  }
}
