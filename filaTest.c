
#include "fila.c"

int main(){
    Processo* processo[4];

    //-> == *().
    //*(processo[3]).pid == processo[3]->pid

    int i, tam;

    for (i=0;i<4;i++){
      processo[i] = (Processo*) malloc(sizeof(Processo));
      processo[i]->pid = i;
    }

    criaFilaProcessosProntos();

    printf("Teste de inserção na lista\n");
    for (i=0;i<4;i++){
      insereElementoNaFila(filaDeProcessosProntos,processo[i]);
      tam = tamanhoFila(filaDeProcessosProntos);
      printf(" tamanho da fila %d \n", tam);
    }

    printf("Teste de remoção na lista\n");
    int pid;
    for ( i = 0; i < 5; i++) {

      pid = removeProcessoDaFila(filaDeProcessosProntos);
      tam = tamanhoFila(filaDeProcessosProntos);
      printf("Foi removido processo %d \n", pid );
      printf(" T: %d \n", tam);
      if (!isFilaVazia(filaDeProcessosProntos)) {
        printf("AFILA NAO ESTA VAZIAS\n");
      }

    }

    puts("printado pids dos processos");
    for(i=0;i<4;i++){
      printf("processo %d tem pid %d\n",i,processo[i]->pid );
    }

    if(isFilaVazia(filaDeProcessosProntos))
      printf("A fila esta vazia \n");
    else{
      tam = tamanhoFila(filaDeProcessosProntos);
      printf("\n\n tamanho da fila %d \n", tam);
    }
    liberaFila(filaDeProcessosProntos);
    return 0;
}
