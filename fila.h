#include "Processo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct elemento{
    Processo processo;
    struct elemento *proximoElementoDaFila;
}Elemento;

typedef struct fila{
    struct elemento *inicio;
    struct elemento *final;
}Fila;

Fila *filaDeProcessosProntos;

void criaFilaProcessosProntos(){
    filaDeProcessosProntos = (Fila*) malloc(sizeof(Fila));
    if (filaDeProcessosProntos != NULL) {
      filaDeProcessosProntos->final = NULL;
      filaDeProcessosProntos->inicio = NULL;
    }
}

void liberaFila(Fila* fila){
    Elemento* elementoAuxiliar;
    while (fila->inicio != NULL) {
        elementoAuxiliar = fila->inicio;
        fila->inicio = fila->inicio->proximoElementoDaFila;
        free(elementoAuxiliar);
    }
    free(fila);
}

bool isFilaVazia(Fila* fila){
    if (fila == NULL) {
      return true;
    }
    if (fila->inicio == NULL){
      return true;
    }
    return false;
}

bool insereElementoNaFila(Fila* fila, Processo processo){
    Elemento *elementoAuxiliar = (Elemento*) malloc(sizeof(Elemento));
    if (elementoAuxiliar == NULL) {
        return false;
    }

    elementoAuxiliar->processo = processo;
    elementoAuxiliar->proximoElementoDaFila = NULL;

    if (fila->final == NULL) {
      fila->inicio = elementoAuxiliar;
    }
    else {
        fila->final->proximoElementoDaFila = elementoAuxiliar;
    }

    fila->final = elementoAuxiliar;
    return true;
}

Processo removeProcessoDaFila(Fila* fila){
    if (fila == NULL) {
      Processo processo;
      return processo;
    }

    if (fila->inicio == NULL) {
      Processo processo;
      return processo;
    }

    Elemento *elementoAuxiliar = fila->inicio;

    Processo processoRetorno = elementoAuxiliar->processo;

    fila->inicio = fila->inicio->proximoElementoDaFila;
    if (fila->inicio == NULL) {
        fila->final = NULL;
    }

    free(elementoAuxiliar);
    return processoRetorno;
}

int tamanhoFila(Fila* fila){
  if(fila == NULL){
      return 0;
  }
  int cont = 0;

  Elemento* elementoAuxiliar = fila->inicio;
  while (elementoAuxiliar != NULL){
    cont++;
    elementoAuxiliar = elementoAuxiliar->proximoElementoDaFila;
  }
  return cont;
}
