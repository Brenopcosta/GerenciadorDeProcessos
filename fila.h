typedef struct fila{
    Processo *inicio;
    Processo *fim;
}Fila;

Fila filaDeProcessosProntos;

void inicializaFila(){
    filaDeProcessosProntos -> inicio = malloc(sizeof(Processo));  
    filaDeProcessosProntos -> fim = filaDeProcessosProntos -> inicio;
}

void inserirProcessoNaFilaDeProntos(Fila *fila , Processo processo){
    
}

