#include "Vertice.h"

Vertice::Vertice(int identificador) {
    id = identificador;
    frequencia = 0;
}

int Vertice::grau(){
    return adj.size();
}
