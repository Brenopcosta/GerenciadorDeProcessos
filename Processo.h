typedef struct Processos{
  int pid;
  int tempoDeExecucaoTotal;
  int tempoDeExecucaoAtual;
  int tempoDeTimeSlice;
  char status[10];
}Processo;
