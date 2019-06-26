from dataclasses import dataclass
from typing import List

from Python.GerenciadorDeProcessos import Pagina


def contem(a,b):
    if a in b:
        return True
    else:
        return False
@dataclass
class Pagina:
    idPadina : int



@dataclass
class Processo:
    id: int
    listaDePaginas: List[Pagina]



def main():
    processos = []
    processos.append(Processo(1,[Pagina(1),Pagina(2)]))
    listaDePagina = []
    processo = processos.pop(0)

    listaDePagina = processo.listaDePaginas
    print(listaDePagina.pop(0))

    return 1

main()