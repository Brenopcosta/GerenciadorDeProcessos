from dataclasses import dataclass
import random

@dataclass
class Processo:
    pid: int
    tempoDeExecucaoTotal: int
    tempoDeExecucaoAtual: int
    tempoDePedidaDeIO: int
    tempoDeVoltaDeIO: int
    tipoDeIO: int
    status: str

VOLTA_IO_IMPRESSORA = 5
VOLTA_IO_DISCO = 2
VOLTA_IO_FITA = 6
TIME_SLICE = 3
filaDeAltaPrioridade = []
filaDeBaixaPrioridade = []
filaDeProcessosProntos = []
filaDeProcessosParados = []
GerenciadorAtivo = True
NUMERO_DE_PROCESSOS = 2
processos = []
tempoDoGerenciador = 0


def inicializaProcesso():
    for i in range(0, NUMERO_DE_PROCESSOS):
        tempoDeExecucaoTotal = random.randint(1,15)
        tempoDePedidaDeIO = random.randint(1, tempoDeExecucaoTotal)
        tempoDeVoltaDeIO = 500
        tipoDeIO = random.randint(1, 3)
        processos.append(Processo(i, tempoDeExecucaoTotal, 0, tempoDePedidaDeIO, tempoDeVoltaDeIO, tipoDeIO, "Pronto"))
        print(processos[i])
    return


def executaProcesso():
    global tempoDoGerenciador
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
            print("O processo vai voltar no tempo:" + str(processo.tempoDeVoltaDeIO))
            tempoDoGerenciador = tempoDoGerenciador + 1
        else:
            if processo.tempoDeExecucaoTotal == processo.tempoDeExecucaoAtual:
                processo.status = "Terminado"
                tempoDoGerenciador = tempoDoGerenciador + 1
            elif processo.status != "Parado":
                tempoDoGerenciador = tempoDoGerenciador + 1
                processo.tempoDeExecucaoAtual = processo.tempoDeExecucaoAtual + 1
                print("Executando o processo de PID " + str(processo.pid) + " no tempo " + str(processo.tempoDeExecucaoAtual))
                print("Tempo de execucao do gerenciador: " + str(tempoDoGerenciador) + " u.t.")
            else:
                tempoDoGerenciador = tempoDoGerenciador + 1
    return


def verificarFilaDeAltaPrioridade():
    if filaDeAltaPrioridade:
        filaDeProcessosProntos.append(filaDeAltaPrioridade.pop(0))
    elif filaDeBaixaPrioridade:
        filaDeProcessosProntos.append(filaDeBaixaPrioridade.pop(0))
    return


def verificarVoltaDeIO():
    for i in range(0, NUMERO_DE_PROCESSOS):
        if processos[i].tempoDeVoltaDeIO >= tempoDoGerenciador:
            if processos[i].tipoDeIO == 1:
                if processos[i] not in filaDeAltaPrioridade:
                    filaDeAltaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 2:
                if processos[i] not in filaDeBaixaPrioridade:
                    filaDeBaixaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 3:
                if processos[i] not in filaDeAltaPrioridade:
                    filaDeAltaPrioridade.append((processos[i]))
    return


def isRodadaOciosa():
    if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade:
        return True
    else:
        return False


def isTodosOsProcessosTerminados():
    numeroDeProcessosTerminados = 0
    for i in range(0, NUMERO_DE_PROCESSOS):
        if processos[i].status == "Terminado":
            numeroDeProcessosTerminados = numeroDeProcessosTerminados + 1
    if numeroDeProcessosTerminados == NUMERO_DE_PROCESSOS:
        return True
    return False


def main():
        inicializaProcesso()
        numeroRodada = 0
        global tempoDoGerenciador, GerenciadorAtivo
        for i in range(0, 2):
            filaDeAltaPrioridade.append(processos[i])
        while GerenciadorAtivo:
            if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade and isTodosOsProcessosTerminados():
                print("Gerenciador terminou com tempo de executao total de: " + str(tempoDoGerenciador) + " u.t.")
                GerenciadorAtivo = False
            print("Rodada " + str(numeroRodada) + " .................................")
            verificarFilaDeAltaPrioridade()
            verificarVoltaDeIO()
            if isRodadaOciosa():
                print("Rodada ociosa")
                numeroRodada = numeroRodada + 1
                tempoDoGerenciador = tempoDoGerenciador + 1
            executaProcesso()
            numeroRodada = numeroRodada + 1
        return


main()
