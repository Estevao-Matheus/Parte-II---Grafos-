#include <iostream>
#include <cstring>
#include <ctime>
#include "Metodo.h"

using namespace std;

static void usage()
{
    cout << "\nUso:\n" <<
        "    Solve [metodo] [opcoes] <arquivo de entrada>\n\n" <<
        "Metodo:\n" <<
        "    -g          Guloso\n" <<
        "    -gr         Guloso Randomizado\n" <<
        "       Opcoes:\n" <<
        "           -a=value          Alfa [0.0 a 1.0] (padrao: 0.5)\n\n"<<
        "           -it=value         Quantidade de iteracoes[int positivo] (padrao: 100)\n"<<
        "    -grr        Guloso Randomizado Reativo\n"<<
        "       Opcoes:\n" <<
        "           -ar=value         Quantidade de alfas[int positivo] Ex: -ar=3 alfas={0,33 ; 0,66; 1.0} (padrao: 5)\n"<<
        "           -it=value         Quantidade de iteracoes[int positivo] (padrao: 1000)\n"<<
        "           -br=value         Quantidade de iteracoes ate trocar de alfa[int positivo] (padrao: 1[troca a toda iteracao])\n"<<
        "           -gr=value         Quantidade de iteracoes para recalcular as probabilidades[int positivo] (padrao: 100)\n\n"<<
        "Opcoes:\n" <<
        "    -?          Mostrar essa ajuda\n" <<
        "    -s=value    Seed do randomico [int positivo] (padrao: time(NULL))\n";
}

int main(int argC, const char * argV[]) {
    time_t init = time(NULL);

    if (argC < 2)
    {
        usage();
        return 1;
    }

    srand(time(NULL));

    // 0 Guloso
    // 1 Guloso Randomizado
    // 2 Guloso Randomizado Reativo
    int metodo = 0;
    float alfa = 0.5;
    int seed = -1;
    bool itchange = false;

    int ar = 5;
    int it = 3000;
    int br = 1;
    int gr = 100;

    int argInd;
    for(argInd = 1; argInd < argC; argInd++) {
        
        if (argV[argInd][0] != '-')
            break;

        if (!strcmp(argV[argInd], "-?")) {
            usage();
            return 2;
        } else if(!strcmp(argV[argInd], "-g")) {
            metodo = 0;
        } else if(!strcmp(argV[argInd], "-gr")) {
            metodo = 1;
        } else if(!strcmp(argV[argInd], "-grr")) {
           metodo = 2; 
        } else if (!strncmp(argV[argInd], "-a=", 3)) {
            const char* const parm = &argV[argInd][3];

            alfa = atof(parm);
            if(alfa > 1.0 || alfa < 0.0) {
                cout << "Valor invalido para -a=: " << parm << endl;
                return 2;
            }
        } else if (!strncmp(argV[argInd], "-s=", 3)) {
            const char* const parm = &argV[argInd][3];

            seed = atoi(parm);
            if(seed < 0) {
                cout << "Valor invalido para -s=: " << parm << endl;
                return 2;
            }
        } else if (!strncmp(argV[argInd], "-ar=", 4)) {
            const char* const parm = &argV[argInd][4];

            ar = atoi(parm);
            if(ar <= 0) {
                cout << "Valor invalido para -ar=: " << parm << endl;
                return 2;
            }
        } else if (!strncmp(argV[argInd], "-it=", 4)) {
            const char* const parm = &argV[argInd][4];

            it = atoi(parm);
            if(it <= 0) {
                cout << "Valor invalido para -it=: " << parm << endl;
                return 2;
            }
            itchange = true;
        } else if (!strncmp(argV[argInd], "-br=", 4)) {
            const char* const parm = &argV[argInd][4];

            br = atoi(parm);
            if(br <= 0) {
                cout << "Valor invalido para -br=: " << parm << endl;
                return 2;
            }
        } else if (!strncmp(argV[argInd], "-gr=", 4)) {
            const char* const parm = &argV[argInd][4];

            gr = atoi(parm);
            if(gr <= 0) {
                cout << "Valor invalido para -gr=: " << parm << endl;
                return 2;
            }
        }

    }
    
    if (argInd != argC - 1) {
        usage();
        return 1;
    }

    cout << "Lendo o arquivo: " << argV[argInd] << "\n\n";
    Metodo* m = new Metodo(argV[argInd]);
    if(m->erro) {
        cout << "Erro na leitura do arquivo!" << endl;
        return 3;
    }
    cout << "Grafo possui " << m->n << " nos e " << m->k << " arestas! \n\n";

    switch(metodo){
        case 0:
            cout << "Executando algoritmo Guloso...\n\n";

            m->Guloso();

            cout << "Interferencia Total: " << m->sumInterferencia << endl;
            m->imprimeGrafo(m->grafo);
            break;
        case 1:
            cout << "Executando algoritmo Guloso Randomizado...\n\n";
            if(seed != -1) {
                srand(seed);
                cout << "Seed: " << seed << "\n";
            }

            if(!itchange) 
                it = 100;

            cout << "Alfa: " << alfa << "\n";
            cout << "Quantidade de iteracoes: " << it << "\n\n";
            
            m->GulosoRandomizado(alfa, it);

            cout << "\nGrafo com Menor Interferencia encontrado: " << m->sumMenorInterferencia << endl;
            m->imprimeGrafo(m->getMelhorGrafo());
            break;
        case 2:
            if(seed != -1) {
                srand(seed);
                cout << "Seed: " << seed << "\n";
            }

            if(!itchange) 
                it = 1000;

            cout << "Executando algoritmo Guloso Randomizado Reativo...\n\n";
            cout << "Quantidade de alfas: " << ar << "\n";
            cout << "Quantidade de iteracoes: " << it << "\n";
            cout << "Quantidade de iteracoes para trocar de alfa: " << br << "\n";
            cout << "Quantidade de iteracoes para recalcular as probabilidades: " << gr << "\n\n";
            m->GulosoRandomizadoReativo(ar, br, gr, it);

            cout << "\nGrafo com Menor Interferencia encontrado: " << m->sumMenorInterferencia << endl;
            m->imprimeGrafo(m->getMelhorGrafo());
            break;
    }
    cout << "Tempo total de execucao: " << time(NULL)-init << " segundos\n";
    delete(m);

    return 0;
}
