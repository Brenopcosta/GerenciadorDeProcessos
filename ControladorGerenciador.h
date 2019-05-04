#define TIME_SLICE 3
#define VOLTA_IO_IMPRESSORA 5
#define VOLTA_IO_DISCO 2
#define VOLTA_IO_FITA 6

int tempoDoGerenciador = 0 ;
bool isGerenciadorLigado = true;



//Verifica se existe processos na fila de alta prioridade, caso sim adiciona estes processos na fila de prontos,
// caso não Verificase há processos na fila de baixa prioridade e adiciona na fila de prontos
void verificaFilaDeAltaPrioridade() {
    if(!isFilaVazia(filaDeAltaPrioridade)){
        insereElementoNaFila(filaDeProcessosProntos, removeProcessoDaFila(filaDeAltaPrioridade));
    }
    else{
      if (!isFilaVazia(filaDeBaixaPrioridade)) {
        insereElementoNaFila(filaDeProcessosProntos, removeProcessoDaFila(filaDeBaixaPrioridade));
      }
    }
}

bool isTodosOsProcessosTerminados(){
    int i, numeroDeProcessosTerminados;
    for (i = 0; i < NUMERO_DE_PROCESSOS; i++) {
      if (strcmp(processo[i]->status , "terminado")) {
        numeroDeProcessosTerminados++;
      }
    }
    if (numeroDeProcessosTerminados == NUMERO_DE_PROCESSOS) {
      return true;
    }
    return false;
}

void verificaTerminoDeGerenciador() {
    if(isFilaVazia(filaDeProcessosProntos) && isFilaVazia(filaDeBaixaPrioridade) && isFilaVazia(filaDeAltaPrioridade) && isTodosOsProcessosTerminados()){
        printf("O gerenciador terminou com tempo de execucao total de : %d u.t \n",tempoDoGerenciador );
        isGerenciadorLigado = false;
    }
}

bool isRodadaOciosa(){
    if(isFilaVazia(filaDeProcessosProntos) && isFilaVazia(filaDeBaixaPrioridade) && isFilaVazia(filaDeAltaPrioridade) ){
      if (!isTodosOsProcessosTerminados()) {
        return true;
      }
    }
    else{
      return false;
    }
}

void executaProcesso(){
    int pidDoProcesso;
    int i;

    Processo *processoEmExecucao = removeProcessoDaFila(filaDeProcessosProntos);
    pidDoProcesso = processoEmExecucao->pid;

    for (i = 0; i < TIME_SLICE; i++) {
        if (processo[pidDoProcesso]->tempoDeExecucaoAtual == processo[pidDoProcesso]->tempoDePedidaDeIO) {
            printf(" Processo de pid :%d pediu I/O \n",processo[pidDoProcesso]->pid);

            switch (processo[pidDoProcesso]->tipoDeIO) {
              case 1:
                processo[pidDoProcesso]->tempoDeVoltaDeIO = tempoDoGerenciador+VOLTA_IO_IMPRESSORA;
                break;
              case 2:
                processo[pidDoProcesso]->tempoDeVoltaDeIO = tempoDoGerenciador+VOLTA_IO_DISCO;
                break;
              case 3:
                processo[pidDoProcesso]->tempoDeVoltaDeIO = tempoDoGerenciador+VOLTA_IO_FITA;
                break;
            }
            strcpy(processo[pidDoProcesso]->status, "parado");
            break;
        }
        else{
        processo[pidDoProcesso]->tempoDeExecucaoAtual++;
          if (processo[pidDoProcesso]->tempoDeExecucaoTotal == processo[pidDoProcesso]->tempoDeExecucaoAtual) {
            strcpy(processo[pidDoProcesso]->status, "terminado");
          }
          else{
          tempoDoGerenciador++;
          printf("Executando o processo de pid %d\n",processo[pidDoProcesso]->pid);
          printf("Tempo de execucao do gerenciador: %d u.t \n\n",tempoDoGerenciador);

        }
      }
    }
}

void verificarVoltaDeIO(){
    int i ;
    for(i=0;i<NUMERO_DE_PROCESSOS;i++){
      if(processo[i]->tempoDeVoltaDeIO >= tempoDoGerenciador){
        switch (processo[i]->tipoDeIO) {
          case IO_IMPRESSORA:
            insereElementoNaFila(filaDeAltaPrioridade, processo[i]);
            break;
          case IO_DISCO:
            insereElementoNaFila(filaDeBaixaPrioridade, processo[i]);
            break;
          case IO_FITA_MAGNETICA:
            insereElementoNaFila(filaDeAltaPrioridade, processo[i]);
            break;
        }
      }
    }
}
