#ifndef METODO_H_INCLUDED
#define METODO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "No.h"

using namespace std;

class Metodo{
    public:
        int n; //Número de nós
        int k; //Número de arestas
        bool erro; //Booleano para definir se houve erro ao ler o arquivo
        vector<No*> grafo; //Grafo
        float sumInterferencia; //Interferencia do Grafo
        vector<int> grafoFrequencias; //Melhor sequencia de frequencias
        float sumMenorInterferencia = -1; //Interferencia do Melhor Grafo

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
        Metodo(string sarq);
        void imprimeGrafo(vector<No*> graph);
        static bool algoritmoOrdenacao(No* a, No* b);
        void resetaGrafo();
        float getInterferencia(int freq1, int freq2);
        vector<No*> getMelhorGrafo();
        void Guloso();
        void GulosoRandomizado(double alfaR, int itTotal);
        void GulosoRandomizadoReativo(int alfaRR, int betaRR, int gammaRR, int itTotal);
    private:
        float selecionaFrequencia(No* no);
        float GulosoRandomizado(double alfaR);
};

#endif // MTSP_H_INCLUDED













