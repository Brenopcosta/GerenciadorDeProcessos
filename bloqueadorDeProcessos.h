#include <stdlib.h>
#include <string.h>
#include <time.h>

void bloqueiaProcesso(int i) {
    strcpy(processo[i].status, "Bloqueado");
}
