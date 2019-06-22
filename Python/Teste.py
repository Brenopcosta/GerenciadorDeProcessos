def contem(a,b):
    if a in b:
        return True
    else:
        return False


def main():
    fila=[1,2,3]
    contem(1, fila)

    fila.remove(1)
    return 1

main()