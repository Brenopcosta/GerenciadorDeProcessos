import random
from dataclasses import dataclass
from typing import List


@dataclass
class Pagina:
    idPagina: int
    idProcesso: int


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
    listaDePaginas: List[Pagina]
    workingSet: List[Pagina]


CONTADOR_PAGINAS = 0
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
NUMERO_DE_PROCESSOS = 17
processos = []
tempoDoGerenciador = 0
memoriaPrincipal = []


def monitorDeCriacaoDeProcessos():
    if len(processos) < NUMERO_DE_PROCESSOS and tempoDoGerenciador % 3 == 0:
        criaProcesso()


# função retorna uma lista de páginas
def criaPaginasParaProcesso(idDoProcesso):
    global CONTADOR_PAGINAS
    paginas = []
    for i in range(1, random.randint(2, 64)):
        paginas.append(Pagina(CONTADOR_PAGINAS, idDoProcesso))
        CONTADOR_PAGINAS += 1
    return paginas


def criaProcesso():
    global CONTADOR_PIDS
    tempoDeExecucaoTotal = random.randint(1, 15)
    tempoDePedidaDeIO = random.randint(1, tempoDeExecucaoTotal)
    tempoDeVoltaDeIO = -1
    tipoDeIO = random.randint(1, 3)
    processos.append(
        Processo(CONTADOR_PIDS, tempoDoGerenciador, tempoDeExecucaoTotal, 0, tempoDePedidaDeIO, tempoDeVoltaDeIO,
                 tipoDeIO, "Pronto", criaPaginasParaProcesso(CONTADOR_PIDS), []))
    filaDeProcessosProntos.append(processos[CONTADOR_PIDS])
    print("Novo processo criado no tempo " + str(tempoDoGerenciador) + " e com PID " + str(CONTADOR_PIDS))
    print("Tempo de execução: " + str(tempoDeExecucaoTotal))
    print("Tempo de pedida de IO: " + str(tempoDePedidaDeIO))
    print("IO do tipo " + str(tipoDeIO))
    processo = processos[CONTADOR_PIDS]
    print("Processo criou as paginas: " + str(processo.listaDePaginas))
    print("Processo adicionado na fila de prontos")
    CONTADOR_PIDS += 1


# ------------------------------------------------------------------
def isProcessoComWorkingSetNaMemoria(idProcessoDado):
    for i in range(0, len(memoriaPrincipal) - 1):
        if memoriaPrincipal[i] == idProcessoDado:
            return True
    return False


def moveWorkingSetParaFrenteDaMemoriaPrincipal(processo):
    for i in range(len(memoriaPrincipal) - 1, -1, -1):
        if memoriaPrincipal[i] == processo:
            memoriaPrincipal.insert(0, memoriaPrincipal.pop(i))


def liberaEspacoNaMemoriaPrincipal():
    print("Liberando Espaco na memoria")
    while len(memoriaPrincipal) > 60:
        workingSetLocal = []
        idProcessoASerRemovido = memoriaPrincipal[len(memoriaPrincipal) - 1].idProcesso
        for i in range(len(memoriaPrincipal) - 1, -1, -1):
            if memoriaPrincipal[i].idProcesso == idProcessoASerRemovido:
                workingSetLocal.insert(0, memoriaPrincipal.pop(i))

        processos[idProcessoASerRemovido].workingSet = workingSetLocal


def preparaProcessoParaExecução(processo):
    print("Preparando processo de PID " + str(processo.pid) + " para ser executado")
    if isProcessoComWorkingSetNaMemoria(processo.pid):
        moveWorkingSetParaFrenteDaMemoriaPrincipal(processo)
    else:
        if len(processo.workingSet):
            if len(memoriaPrincipal) >= 60:
                liberaEspacoNaMemoriaPrincipal()
            memoriaPrincipal.insert(0, processo.workingSet)


def temEspacoNoWorkingSet(idProcesso):
    contadorDePaginasNoWorkingSet = 0
    for i in range(0, len(memoriaPrincipal) - 1):
        processo = memoriaPrincipal[i]
        if processo.idProcesso == idProcesso:
            contadorDePaginasNoWorkingSet += 1
    if contadorDePaginasNoWorkingSet < 4:
        return True
    elif contadorDePaginasNoWorkingSet == 4:
        return False
    else:
        print("WorkingSet defeituoso")
        return False


def removePaginaDoWorkingSet(idProcesso):
    workingSetLocal = []
    for i in range(0, len(memoriaPrincipal) - 1):
        if memoriaPrincipal[i].idProcesso == idProcesso:
            workingSetLocal.append(memoriaPrincipal[i])
    print("Removendo a " + str(workingSetLocal[len(workingSetLocal) - 1]))
    memoriaPrincipal.remove(workingSetLocal[len(workingSetLocal) - 1])


def chamaPagina(processo):
    listaDePaginaLocal = processo.listaDePaginas
    paginaLocal = listaDePaginaLocal[random.randint(0, len(listaDePaginaLocal) - 1)]
    print("Processo precisa da pagina " + str(paginaLocal.idPagina))
    return paginaLocal.idPagina


def inserePaginaNaMemoriaPrincipal(pagina):
    if temEspacoNoWorkingSet(pagina.idProcesso) == False:
        print("O Processo " + str(pagina.idProcesso) + " excedeu o limite de paginas simultaneas na memoria")
        removePaginaDoWorkingSet(pagina.idProcesso)
    elif len(memoriaPrincipal) >= 64:
        print("MEMORIA CHEIA, LIBERANDO ESPACO ....")
        liberaEspacoNaMemoriaPrincipal()
    memoriaPrincipal.insert(0, pagina)


def buscaPagina(processo, idDaPagina):
    pagina = Pagina(idDaPagina, processo.pid)
    if pagina in memoriaPrincipal:
        memoriaPrincipal.remove(pagina)
        memoriaPrincipal.insert(0, pagina)
    else:
        print("PAGE FAULT!!!")
        inserePaginaNaMemoriaPrincipal(pagina)


# -----------------------------------------------------------------------------------------------

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
            print("O processo vai voltar no tempo: " + str(processo.tempoDeVoltaDeIO))
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
                preparaProcessoParaExecução(processo)
                print("Executando o processo de PID " + str(processo.pid) + " no tempo " + str(
                    processo.tempoDeExecucaoAtual))
                buscaPagina(processo, chamaPagina(processo))
                print("Situação atual da memória principal: " + str(memoriaPrincipal))
                print("Espaço usado na memoria principal: " + str(len(memoriaPrincipal)))
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
        if processos[i].tempoDeVoltaDeIO <= tempoDoGerenciador and processos[i].tempoDeVoltaDeIO != 0 \
                and processos[i].status == "Parado":
            print("Processo " + str(processos[i].pid) + " voltou do I/O no tempo: " + str(
                processos[i].tempoDeVoltaDeIO) + " u.t")
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
    global tempoDoGerenciador, GerenciadorAtivo, CONTADOR_PIDS
    while GerenciadorAtivo:
        monitorDeCriacaoDeProcessos()
        if not filaDeProcessosProntos and not filaDeBaixaPrioridade and not filaDeAltaPrioridade and isTodosOsProcessosTerminados():
            print("Gerenciador terminou com tempo de executao total de: " + str(tempoDoGerenciador) + " u.t.")
            GerenciadorAtivo = False
            return
        verificarFilaDeAltaPrioridade()
        verificarVoltaDeIO()
        executaProcesso()
        print("Tempo do gerenciador: " + str(tempoDoGerenciador))
    return


main()
