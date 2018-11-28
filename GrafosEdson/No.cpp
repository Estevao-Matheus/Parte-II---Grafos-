#include "No.h"

No::No(int identificador){
    id = identificador;
    frequencia = 0;
}

int No::grau(){
    return adj.size();
}
