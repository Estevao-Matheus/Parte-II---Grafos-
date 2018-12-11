#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

class Vertice{
    public:
        int id; //ID do vertice
        int frequencia; //Frequencia do vertice
        vector<Vertice*> adj; //Lista de Adjacencia do vertice

        Vertice(int identificador);
        int grau();
};

#endif // VERTICE_H_INCLUDED
