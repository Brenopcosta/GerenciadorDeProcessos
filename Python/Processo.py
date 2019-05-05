from dataclasses import dataclass

@dataclass
class Processo:
    pid: int
    tempoDeExecucaoTotal: int
    tempoDeExecucaoAtual: int
    tempoDePedidaDeIO: int
    tempoDeVoltaDeIO: int
    tipoDeIO: int
    status: str