from IniciadorDeProcessos import*
from ControladorDoGerenciador import*

VOLTA_IO_IMPRESSORA = 5
VOLTA_IO_DISCO = 2
VOLTA_IO_FITA = 6
TIME_SLICE = 3
tempoDoGerenciador = 0
filaDeAltaPrioridade = []
filaDeBaixaPrioridade = []
filaDeProcessosProntos = []
GerenciadorAtivo = True


def main():
    numeroRodada = 0
    global tempoDoGerenciador, GerenciadorAtivo
    inicializaProcesso()
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
