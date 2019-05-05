#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Processo.h"

typedef struct elemento{
    Processo* processo;
    struct elemento *proximoElementoDaFila;
}Elemento;

#endif

#ifndef FILA_H
#define FILA_H
typedef struct fila{
    struct elemento *inicio;
    struct elemento *final;
}Fila;
#endif

Fila *filaDeProcessosProntos;
Fila *filaDeAltaPrioridade;
Fila *filaDeBaixaPrioridade;

void criaFilaProcessosProntos(){
    filaDeProcessosProntos = (Fila*) malloc(sizeof(Fila));
    if (filaDeProcessosProntos != NULL) {
      filaDeProcessosProntos->final = NULL;
      filaDeProcessosProntos->inicio = NULL;
    }
}

void criaFilaDeAltaPrioridade(){
    filaDeAltaPrioridade = (Fila*) malloc(sizeof(Fila));
      if(filaDeAltaPrioridade != NULL){
        filaDeAltaPrioridade->inicio = NULL;
        filaDeAltaPrioridade->final = NULL;
      }
};

void criaFilaDeBaixaPrioridade(){
    filaDeBaixaPrioridade = (Fila*) malloc(sizeof(Fila));
      if(filaDeBaixaPrioridade != NULL){
        filaDeBaixaPrioridade->inicio = NULL;
        filaDeBaixaPrioridade->final = NULL;
      }
};


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

bool insereElementoNaFila(Fila* fila, Processo* processo){
    Elemento *elementoAuxiliar = (Elemento*) malloc(sizeof(Elemento));
    if (elementoAuxiliar == NULL) {
        return false;
    }

    elementoAuxiliar->processo = processo;
    elementoAuxiliar->proximoElementoDaFila = NULL;

    if (fila->inicio == NULL)
      fila->inicio = elementoAuxiliar;
    else
      fila->final->proximoElementoDaFila = elementoAuxiliar;


    fila->final = elementoAuxiliar;
    return true;
}

//retorna PID do processo
int removeProcessoDaFila(Fila* fila){
    int pid;
    if (fila == NULL || fila->inicio == NULL)
      return 20;
    puts("fila nao esta vazia");
    Elemento *elementoAuxiliar = fila->inicio;
    Processo *processoAuxiliar = elementoAuxiliar->processo;
    puts("populou elemento auxiliar\n");
    pid = processoAuxiliar->pid;
    puts("populou o pid\n");
    fila->inicio = fila->inicio->proximoElementoDaFila;
    if (fila->inicio == NULL) {
        fila->final = NULL;
    }

    free(elementoAuxiliar);
    return pid;
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
