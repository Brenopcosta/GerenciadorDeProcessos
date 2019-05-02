#include <stdlib.h>
#include <string.h>

void finalizaProcesso(int i) {
    strcpy(processo[i].status, "Bloqueado");
    strcpy(processo[i].status, "Finalizado");
    printf("\n== Processo de PID : %d está %s\n", processo[i].pid, processo[i].status );
    //printf("Quantidades de processos faltando finalizar: %d ==\n", nProcessos);
}