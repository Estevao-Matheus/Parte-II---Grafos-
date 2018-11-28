#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

class No{
    public:
        int id; //ID do nó
        int frequencia; //Frequencia do nó
        vector<No*> adj; //Vector de adjacências do nó

        No(int identificador);
        int grau();
};

#endif // NO_H_INCLUDED
