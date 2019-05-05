def executaProcesso():
    import main
    processo = main.filaDeProcessosProntos.pop(0)

    for i in range(0, main.TIME_SLICE):
        if processo.tempoDeExecucaoAtual == processo.tempoDePedidaDeIO and\
                processo.status != "Parado":
            print("Processo de PID " + str(processo.pid) + " pediu I/O")
            processo.status = "Parado"
            if processo.tipoDeIO == 1:
                processo.tempoDeVoltaDeIO = main.tempoDoGerenciador + main.VOLTA_IO_IMPRESSORA
            elif processo.tipoDeIO == 2:
                processo.tempoDeVoltaDeIO = main.tempoDoGerenciador + main.VOLTA_IO_DISCO
            elif processo.tipoDeIO == 3:
                processo.tempoDeVoltaDeIO = main.tempoDoGerenciador + main.VOLTA_IO_FITA
        else:
            if processo.tempoDeExecucaoTotal == processo.tempoDeExecucaoAtual:
                processo.status = "Terminado"
            else:
                main.tempoDoGerenciador = main.tempoDoGerenciador + 1
                processo.tempoDeExecucaoAtual = processo.tempoDeExecucaoAtual + 1
                print("Executando o processo de PID " + str(processo.pid) + " no tempo " + str(processo.tempoDeExecucaoAtual))
                print("Tempo de execucao do gerenciador: " + str(main.tempoDoGerenciador) + " u.t.")
    return


def verificarFilaDeAltaPrioridade():
    import main
    if main.filaDeAltaPrioridade:
        main.filaDeProcessosProntos.append(main.filaDeAltaPrioridade.pop(0))
    else:
        main.filaDeProcessosProntos.append(main.filaDeBaixaPrioridade.pop(0))
    return


def verificarVoltaDeIO():
    import IniciadorDeProcessos
    import main
    for i in range(0, IniciadorDeProcessos.NUMERO_DE_PROCESSOS):
        if IniciadorDeProcessos.processos[i].tempoDeVoltaDeIO >= main.tempoDoGerenciador:
            if IniciadorDeProcessos.processos[i].tipoDeIO == 1:
                main.filaDeAltaPrioridade.append(IniciadorDeProcessos.processos[i])
            elif IniciadorDeProcessos.processos[i].tipoDeIO == 2:
                main.filaDeBaixaPrioridade.append(IniciadorDeProcessos.processos[i])
            elif IniciadorDeProcessos.processos[i].tipoDeIO == 3:
                main.filaDeAltaPrioridade.append((IniciadorDeProcessos.processos[i]))
    return


def isRodadaOciosa():
    import main
    if not main.filaDeProcessosProntos and not main.filaDeBaixaPrioridade and not main.filaDeAltaPrioridade:
        return True
    else:
        return False


def isTodosOsProcessosTerminados():
    import IniciadorDeProcessos
    numeroDeProcessosTerminados = 0
    for i in range(0, IniciadorDeProcessos.NUMERO_DE_PROCESSOS):
        if IniciadorDeProcessos.processos[i].status == "Terminado":
            numeroDeProcessosTerminados = numeroDeProcessosTerminados + 1
    if numeroDeProcessosTerminados == IniciadorDeProcessos.NUMERO_DE_PROCESSOS:
        return True
    return False