#define TIME_SLICE 3
#define VOLTA_IO_IMPRESSORA 5
#define VOLTA_IO_DISCO 2
#define VOLTA_IO_FITA 6

int tempoDoGerenciador = 0 ;
bool isGerenciadorLigado = true;

//Verifica se existe processos na fila de alta prioridade, caso sim adiciona estes processos na fila de prontos,
// caso não Verificase há processos na fila de baixa prioridade e adiciona na fila de prontos
void verificaFilaDeAltaPrioridade() {
    int pidDoProcesso;
    if(!isFilaVazia(filaDeAltaPrioridade)){
        pidDoProcesso = removeProcessoDaFila(filaDeAltaPrioridade);
        insereElementoNaFila(filaDeProcessosProntos, processo[pidDoProcesso]);
    }
    if (!isFilaVazia(filaDeBaixaPrioridade)) {
      pidDoProcesso = removeProcessoDaFila(filaDeBaixaPrioridade);
      insereElementoNaFila(filaDeProcessosProntos, processo[pidDoProcesso]);
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
    if(isFilaVazia(filaDeProcessosProntos) && isFilaVazia(filaDeBaixaPrioridade) && isFilaVazia(filaDeAltaPrioridade) && !isTodosOsProcessosTerminados()){
        return true;
    }
    else{
      return false;
    }
}

void executaProcesso(){
    int pidDoProcesso;
    int i;

    pidDoProcesso = removeProcessoDaFila(filaDeProcessosProntos);
    if(pidDoProcesso == 20)
      printf("processo invalido\n");

    for (i = 0; i < TIME_SLICE; i++) {
        if (processo[pidDoProcesso]->tempoDeExecucaoAtual == processo[pidDoProcesso]->tempoDePedidaDeIO) {
            printf("Rodada %d ........................................................\n",tempoDoGerenciador );
            printf(" Processo de pid :%d pediu I/O \n",processo[pidDoProcesso]->pid);
            strcpy(processo[pidDoProcesso]->status, "parado");
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
                      default:
                        puts("Erro na pedida de IO");
                    }
            break;
        }
        else{
          if (processo[pidDoProcesso]->tempoDeExecucaoTotal == processo[pidDoProcesso]->tempoDeExecucaoAtual) {
            printf("Rodada %d ........................................................\n",tempoDoGerenciador );
            strcpy(processo[pidDoProcesso]->status, "terminado");
            printf("O processo de pid: %d terminou\n",processo[pidDoProcesso]->pid );
            break;
          }
          else{
          tempoDoGerenciador++;
          (processo[pidDoProcesso]->tempoDeExecucaoAtual)++;
          printf("Rodada %d ........................................................\n",tempoDoGerenciador );
          printf("Executando o processo de pid %d no tempo %d u.t\n",processo[pidDoProcesso]->pid, processo[pidDoProcesso]->tempoDeExecucaoAtual);
          printf("Tempo de execucao do gerenciador: %d u.t \n\n",tempoDoGerenciador);
        }
      }

    }
}

void verificarVoltaDeIO(){
    int i;
      for(i=0;i<NUMERO_DE_PROCESSOS;i++){
        if(processo[i]->tempoDeVoltaDeIO >= tempoDoGerenciador){
          switch (processo[i]->tipoDeIO) {
            case 1:
              insereElementoNaFila(filaDeAltaPrioridade, processo[i]);
              break;
            case 2:
              insereElementoNaFila(filaDeBaixaPrioridade, processo[i]);
              break;
            case 3:
              insereElementoNaFila(filaDeAltaPrioridade, processo[i]);
              break;
        }
      }
    }
}
