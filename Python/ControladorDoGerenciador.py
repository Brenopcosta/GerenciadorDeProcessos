def executaProcesso():
    from main import filaDeProcessosProntos, TIME_SLICE, filaDeProcessosParados, tempoDoGerenciador, VOLTA_IO_IMPRESSORA, VOLTA_IO_DISCO, VOLTA_IO_FITA
    processo = filaDeProcessosProntos.pop(0)

    for i in range(0, TIME_SLICE):
        if processo.tempoDeExecucaoAtual == processo.tempoDePedidaDeIO and\
                processo.status != "Parado" and processo.status != "Terminado":
            print("Processo de PID " + str(processo.pid) + " pediu I/O")
            processo.status = "Parado"
            filaDeProcessosParados.append(processo)
            if processo.tipoDeIO == 1:
                processo.tempoDeVoltaDeIO = tempoDoGerenciador + VOLTA_IO_IMPRESSORA
            elif processo.tipoDeIO == 2:
                processo.tempoDeVoltaDeIO = tempoDoGerenciador + VOLTA_IO_DISCO
            elif processo.tipoDeIO == 3:
                processo.tempoDeVoltaDeIO = tempoDoGerenciador + VOLTA_IO_FITA
        else:
            if processo.tempoDeExecucaoTotal == processo.tempoDeExecucaoAtual:
                processo.status = "Terminado"
            elif processo.status != "Parado":
                tempoDoGerenciador = tempoDoGerenciador + 1
                processo.tempoDeExecucaoAtual = processo.tempoDeExecucaoAtual + 1
                print("Executando o processo de PID " + str(processo.pid) + " no tempo " + str(processo.tempoDeExecucaoAtual))
                print("Tempo de execucao do gerenciador: " + str(tempoDoGerenciador) + " u.t.")
    return


def verificarFilaDeAltaPrioridade():
    from main import  filaDeAltaPrioridade, filaDeProcessosProntos, filaDeBaixaPrioridade
    if filaDeAltaPrioridade:
        filaDeProcessosProntos.append(filaDeAltaPrioridade.pop(0))
    else:
        filaDeProcessosProntos.append(filaDeBaixaPrioridade.pop(0))
    return


def verificarVoltaDeIO():
    from IniciadorDeProcessos import NUMERO_DE_PROCESSOS, processos
    from main import filaDeAltaPrioridade, filaDeBaixaPrioridade, tempoDoGerenciador
    for i in range(0, NUMERO_DE_PROCESSOS):
        if processos[i].tempoDeVoltaDeIO >= tempoDoGerenciador:
            if processos[i].tipoDeIO == 1:
                filaDeAltaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 2:
                filaDeBaixaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 3:
                filaDeAltaPrioridade.append((processos[i]))
    return


def isRodadaOciosa():
    from main import filaDeProcessosProntos, filaDeBaixaPrioridade, filaDeAltaPrioridade
    if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade:
        return True
    else:
        return False


def isTodosOsProcessosTerminados():
    import IniciadorDeProcessos as i
    numeroDeProcessosTerminados = 0
    for i in range(0, i.NUMERO_DE_PROCESSOS):
        if i.processos[i].status == "Terminado":
            numeroDeProcessosTerminados = numeroDeProcessosTerminados + 1
    if numeroDeProcessosTerminados == i.NUMERO_DE_PROCESSOS:
        return True
    return False