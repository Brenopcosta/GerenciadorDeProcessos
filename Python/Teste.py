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
    processos.append(Processo(1,[Pagina(1),Pagina(2),Pagina(3)]))
    listaDePagina = []
    processo = processos.pop(0)
    listaDePagina = processo.listaDePaginas

    if Pagina(1) in processo.listaDePaginas:
        print ("ESTA NA LISTA DE PAGINAS")

    print(listaDePagina)

    listaDePagina.remove(Pagina(3))
    listaDePagina.insert(0,Pagina(3))
    print(listaDePagina)





    return 1

main()