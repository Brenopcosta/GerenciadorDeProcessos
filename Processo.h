#ifndef PROCESSO_H
#define PROCESSO_H
#define PRIORIDADE_ALTA 2
#define PRIORIDADE_BAIXA 1
#define IO_IMPRESSORA 1
#define IO_DISCO 2
#define IO_FITA_MAGNETICA 3


typedef struct Processos{
  int pid;
  int tempoDeExecucaoTotal;
  int tempoDeExecucaoAtual;
  int tempoDePedidaDeIO;
  int tempoDeVoltaDeIO;
  int tipoDeIO;
  char status[10];
}Processo;

#endif /* PROCESSO_H */
