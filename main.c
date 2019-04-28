#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Processo.h"
#include"InicializadorDeProcessos.h"

int tempoDeExecucaoDoGerenciador = 0;
int i;

void main()
{

  incializaProcesso();

  for(i=0; i<2; i++){
    printf("Dados do processo de PID : %d \n",processo[i].pid);
    printf("Status da execucao do processo :%s\n",processo[i].status);
    printf("Tempo de execucao do processo : %d\n",processo[i].tempoDeExecucao );
    puts("\n\n\n");
  }

  for(i=0; i<2; i++){
    tempoDeExecucaoDoGerenciador = tempoDeExecucaoDoGerenciador+ processo[i].tempoDeExecucao;
  }

  while (tempoDeExecucaoDoGerenciador > 0) {
      for(i=0;i<2;i++){
        while (processo[i].tempoDeExecucao > 0 ) {
          if ((processo[i].tempoDeExecucao - 1) == 0) {
          printf("Processo de PID : %d finalizado \n\n\n\n", processo[i].pid );
          break;
          }
          printf(" Processo de PID: %d executando \n", processo[i].pid);
          printf("Tempo restante de execucao: %d \n", processo[i].tempoDeExecucao);
          printf("Status do processo : %s\n", processo[i].status);

          processo[i].tempoDeExecucao--;
        }
        tempoDeExecucaoDoGerenciador--;
    }
  }
}
