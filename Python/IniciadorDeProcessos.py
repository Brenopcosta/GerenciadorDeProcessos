from Processo import Processo
import random

NUMERO_DE_PROCESSOS = 2
processos = []

def inicializaProcesso():
    for i in range (0, NUMERO_DE_PROCESSOS):
        tempoDeExecucaoTotal = random.randint(1,15)
        tempoDePedidaDeIO = random.randint(1, tempoDeExecucaoTotal)
        tempoDeVoltaDeIO = 500
        tipoDeIO = random.randint(1, 3)
        processos.append(Processo(i, tempoDeExecucaoTotal, 0, tempoDePedidaDeIO, tempoDeVoltaDeIO, tipoDeIO, "Pronto"))
    return