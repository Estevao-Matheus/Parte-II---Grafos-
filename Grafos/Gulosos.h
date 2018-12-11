#ifndef METODO_H_INCLUDED
#define METODO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Vertice.h"

using namespace std;

class Gulosos{
    public:
        int n; //Número de nós
        int k; //Número de arestas
        bool erro; //Booleano usado pra verficar a abertura correta do arquivo
        vector<Vertice*> grafo; //Grafo utilizado
        float somatorioInterferencia; //Interferencia do Grafo
        float somatorioMenorInterferencia = -1; //Interferencia do Melhor Grafo
        vector<int> grafoFrequencias; //Melhor sequencia de frequencias


        float interferencia[196] = {1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                                   0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                                   0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                                   0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                                   0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00, 0.00,
                                   0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00, 0.00,
                                   0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00, 0.00,
                                   0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00, 0.00,
                                   0.00, 0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.54, 0.31, 0.09, 0.00,
                                   0.00, 0.00, 0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.75, 0.50, 0.31, 0.00,
                                   0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.75, 0.54, 0.00,
                                   0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.77, 0.22,
                                   0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.09, 0.31, 0.54, 0.77, 1.00, 0.45,
                                   0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.22, 0.45, 1.00};
        Gulosos(string stringArq);
        void imprimeGrafo(vector<Vertice*> grafo);
        void resetaGrafo();
        vector<Vertice*> getMelhorGrafo();
        static bool algoritmoOrdenacao(Vertice* a, Vertice* b);
        float getInterferencia(int frequencia1, int frequencia2);
        void Guloso();
        void GulosoRandomizado(double alfaR, int itTotal);
        void GulosoRandomizadoReativo(int alfaRR, int betaRR, int gammaRR, int itTotal);
    private:
        float selecionaFrequencia(Vertice* vertice);
        float GulosoRandomizado(double alfaR);
};

#endif // MTSP_H_INCLUDED













