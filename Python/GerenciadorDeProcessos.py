from dataclasses import dataclass
import random
import sys


@dataclass
class Processo:
    pid: int
    tempoDeChegada: int
    tempoDeExecucaoTotal: int
    tempoDeExecucaoAtual: int
    tempoDePedidaDeIO: int
    tempoDeVoltaDeIO: int
    tipoDeIO: int
    status: str


CONTADOR_PIDS = 0
VOLTA_IO_IMPRESSORA = 5
VOLTA_IO_DISCO = 2
VOLTA_IO_FITA = 6
TIME_SLICE = 3
filaDeAltaPrioridade = []
filaDeBaixaPrioridade = []
filaDeProcessosProntos = []
filaDeProcessosParados = []
GerenciadorAtivo = True
NUMERO_DE_PROCESSOS = 4
processos = []
tempoDoGerenciador = 0

def monitorDeCriacaoDeProcessos():
    if len(processos) < NUMERO_DE_PROCESSOS and tempoDoGerenciador%4 == 0:
        criaProcesso()

def criaProcesso():
    global CONTADOR_PIDS
    tempoDeExecucaoTotal = random.randint(1, 15)
    tempoDePedidaDeIO = random.randint(1, tempoDeExecucaoTotal)
    tempoDeVoltaDeIO = -1
    tipoDeIO = random.randint(1, 3)
    processos.append(Processo(CONTADOR_PIDS,tempoDoGerenciador, tempoDeExecucaoTotal, 0, tempoDePedidaDeIO, tempoDeVoltaDeIO, tipoDeIO, "Pronto"))
    filaDeProcessosProntos.append(processos[CONTADOR_PIDS])
    print("Novo processo criado no tempo "+ str(tempoDoGerenciador)+ " e com PID:"+str(CONTADOR_PIDS))
    print("Processo adicionado na fila de prontos")
    print(processos[CONTADOR_PIDS])
    CONTADOR_PIDS += 1


def inicializaProcesso():
    for i in range(0, NUMERO_DE_PROCESSOS):
        criaProcesso()
    return


def executaProcesso():
    global tempoDoGerenciador
    if not filaDeProcessosProntos:
        tempoDoGerenciador = tempoDoGerenciador + 1
        return
    processo = filaDeProcessosProntos.pop(0)

    for i in range(0, TIME_SLICE):
        if processo.tempoDeExecucaoAtual == processo.tempoDePedidaDeIO and \
                processo.status != "Parado" and processo.status != "Terminado":
            print("---------------------------------------------")
            print("Processo de PID " + str(processo.pid) + " pediu I/O")
            processo.tempoDePedidaDeIO = 0
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
            return
        else:
            if processo.tempoDeExecucaoTotal == processo.tempoDeExecucaoAtual:
                print("---------------------------------------------")
                processo.status = "Terminado"
                tempoDoGerenciador = tempoDoGerenciador + 1
                print("O processo de pid: " + str(processo.pid) + " terminou com tempo de turnaound " + str(
                    tempoDoGerenciador - processo.tempoDeChegada))
                return
            elif processo.status != "Parado":
                print("---------------------------------------------")
                tempoDoGerenciador = tempoDoGerenciador + 1
                processo.tempoDeExecucaoAtual = processo.tempoDeExecucaoAtual + 1
                print("Executando o processo de PID " + str(processo.pid) + " no tempo " + str(
                    processo.tempoDeExecucaoAtual))
                print("Tempo de execucao do gerenciador: " + str(tempoDoGerenciador) + " u.t.")
    filaDeBaixaPrioridade.append(processo)
    return


def verificarFilaDeAltaPrioridade():
    if filaDeAltaPrioridade:
        filaDeAltaPrioridade[0].status = "Pronto"
        filaDeProcessosProntos.append(filaDeAltaPrioridade.pop(0))
    elif filaDeBaixaPrioridade:
        filaDeBaixaPrioridade[0].status = "Pronto"
        filaDeProcessosProntos.append(filaDeBaixaPrioridade.pop(0))
    return


def verificarVoltaDeIO():
    for i in range(0, len(processos)):
        if processos[i].tempoDeVoltaDeIO <= tempoDoGerenciador and processos[i].tempoDeVoltaDeIO != 0 and processos[i].status == "Parado":
            print("Processo " + str(processos[i].pid) + " voltou do I/O no tempo :" +str(processos[i].tempoDeVoltaDeIO)+" u.t")
            processos[i].tempoDeVoltaDeIO = 0
            if processos[i].tipoDeIO == 1:
                if processos[i] not in filaDeAltaPrioridade:
                    print("Entrou na fila de alta prioridade")
                    filaDeAltaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 2:
                if processos[i] not in filaDeBaixaPrioridade:
                    print("Entrou na fila de baixa prioridade")
                    filaDeBaixaPrioridade.append(processos[i])
            elif processos[i].tipoDeIO == 3:
                if processos[i] not in filaDeAltaPrioridade:
                    print("Entrou na fila de alta prioridade")
                    filaDeAltaPrioridade.append((processos[i]))
    return


def isRodadaOciosa():
    if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade:
        return True
    else:
        return False


def isTodosOsProcessosTerminados():
    numeroDeProcessosTerminados = 0
    for i in range(0, len(processos)):
        if processos[i].status == "Terminado":
            numeroDeProcessosTerminados = numeroDeProcessosTerminados + 1
    if numeroDeProcessosTerminados == NUMERO_DE_PROCESSOS:
        return True
    return False


def main():
    global tempoDoGerenciador, GerenciadorAtivo , CONTADOR_PIDS
    while GerenciadorAtivo:
        monitorDeCriacaoDeProcessos()
        if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade and isTodosOsProcessosTerminados():
            print("Gerenciador terminou com tempo de executao total de: " + str(tempoDoGerenciador) + " u.t.")
            GerenciadorAtivo = False
            return
        verificarFilaDeAltaPrioridade()
        verificarVoltaDeIO()
        executaProcesso()
        print("Tempo do gerenciador:" + str(tempoDoGerenciador))
    return


main()