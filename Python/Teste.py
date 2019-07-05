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

vetor = [1,2,3,4,5]

def nTaNoVetor(n):
    for i in range(0,len(vetor)-1):
        if vetor[i] == n:
            return True
    return False
def main():
    processos = []
    processos.append(Processo(1,[Pagina(1),Pagina(2),Pagina(3)]))
    listaDePagina = []
    processo = processos.pop(0)
    listaDePagina = processo.listaDePaginas

    if Pagina(1) in processo.listaDePaginas:
        print("ESTA NA LISTA DE PAGINAS")
        print(listaDePagina[2].idPadina)
    print(listaDePagina)
    listaDePagina.insert(0,listaDePagina.pop(2))
    print(listaDePagina)

    print("Espaço para teste 2")
    print(str(nTaNoVetor(2)))

    for i in range(10,-1,-1):
        print(str(i))

    vetor2 = [7,8,9]
    for i in range(len(vetor2)-1,-1,-1):
        vetor.insert(0,vetor2[i])

    print(str(vetor))
    return 1

main()