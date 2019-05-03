#include "fila.h"

void main(){
    Processo processo[4];

    int i, tam;

    for (i=0;i<4;i++){
      processo[i].pid = i;
    }

    criaFilaProcessosProntos();

    for (i=0;i<4;i++){
      insereElementoNaFila(filaDeProcessosProntos,processo[i]);
      tam = tamanhoFila(filaDeProcessosProntos);
      printf(" tamanho da fila %d \n", tam);
    }

    puts("\n\n fim do primeiro laco \n\n");

    for ( i = 0; i < 5; i++) ;{
      removeProcessoDaFila(filaDeProcessosProntos);
      tam = tamanhoFila(filaDeProcessosProntos);
      printf(" tamanho da fila %d \n", tam);
    }

    tam = tamanhoFila(filaDeProcessosProntos);
    printf("\n\n tamanho da fila %d \n", tam);
    liberaFila(filaDeProcessosProntos);

    isFilaVazia(filaDeProcessosProntos);
}
