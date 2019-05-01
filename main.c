#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Processo.h"
#include"InicializadorDeProcessos.h"

int tempoDeExecucaoDoGerenciador = 0;
int i;
int nProcessos = NUMERO_DE_PROCESSOS;

void main()
{

  incializaProcesso();

  for(i=0; i<2; i++){
    printf("\nDados do processo de PID : %d \n",processo[i].pid);
    printf("Status da execucao do processo :%s\n",processo[i].status);
    printf("Tempo de execucao do processo : %d\n",processo[i].tempoDeExecucao );
  }

  for(i=0; i<2; i++){
    tempoDeExecucaoDoGerenciador = tempoDeExecucaoDoGerenciador+ processo[i].tempoDeExecucao;
  }

  while (tempoDeExecucaoDoGerenciador > 0 && nProcessos > 0)  {
      for(i=0;i<2;i++){
        while (processo[i].tempoDeExecucao > 0 ) {
          if ((processo[i].tempoDeExecucao - 1) == 0 && processo[i].status != "Finalizado" ){
          nProcessos--;
          strcpy(processo[i].status, "Finalizado");
          printf("\n== Processo de PID : %d %s\n", processo[i].pid, processo[i].status );
          printf("Quantidades de processos faltando finalizar: %d ==\n", nProcessos);
          break;
          }          
          processo[i].tempoDeExecucao--;
          printf("\n== Processo de PID: %d executando \n", processo[i].pid);
          printf("Tempo restante de execucao: %d \n", processo[i].tempoDeExecucao);
          printf("Status do processo: %s ==\n", processo[i].status);
        }
        tempoDeExecucaoDoGerenciador--;
    }
  }
}
