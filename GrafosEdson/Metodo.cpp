#include "Metodo.h"

Metodo::Metodo(string sarq) {
    fstream arq;
    erro = false;

    try{
        arq.open(sarq.c_str());
        if(arq.is_open()){
            arq >> n;
            grafo = vector<No*>(n);

            for(int i = 0; i < n; i++)
                grafo.at(i) = new No(i+1);

            //Lendo as arestas
            k = 0;
            int x, y;
            while(arq >> x >> y){
                k++;
                x--; y--;

                grafo.at(x)->adj.push_back(grafo.at(y));
                grafo.at(y)->adj.push_back(grafo.at(x));
            }

        } else 
            erro = true;
    } catch (...) {
        cout << "O Arquivo provavelmente esta fora do padrao!" << endl;
        erro = true;
    }
}

//Imprime o Grafo na tela
void Metodo::imprimeGrafo(vector<No*> g){
    cout << "Grafo:\n";
    for(int i = 0; i < g.size(); i++){
        cout << "- " << g.at(i)->id << " [freq:" << g.at(i)->frequencia << "] -> ";
        for(int j = 0; j < g.at(i)->adj.size(); j++){
            cout << "[" << g.at(i)->adj.at(j)->id << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

//Função para resetar o Grafo
void Metodo::resetaGrafo(){
    for(int i = 0; i < grafo.size(); i++)
        grafo.at(i)->frequencia = 0;
}
vector<No*> Metodo::getMelhorGrafo(){
    if(grafoFrequencias.size() > 0) {
        for(int i = 0; i < grafoFrequencias.size(); i++)
            grafo.at(i)->frequencia = grafoFrequencias.at(i);
    }

    return grafo;
}

//Função para ver a interferência
float Metodo::getInterferencia(int freq1, int freq2){
    return interferencia[((freq1-1)*14)+(freq2-1)];
}

//Função para selecionar a Frequencia
float Metodo::selecionaFrequencia(No* no){
    int bestF;
    float bestInter;

    for(int f = 1; f <= 14; f++) {
        float interSum = 0.0;

        for(No* adj: no->adj) {
            if(adj->frequencia == 0)
                continue;

            interSum += getInterferencia(f, adj->frequencia);
        }

        if(f == 1 || interSum <= bestInter) {
            bestF = f;
            bestInter = interSum;
        }
    }

    no->frequencia = bestF;
    return bestInter;
}

//Função auxiliar para a função e sort
bool Metodo::algoritmoOrdenacao(No* a, No* b){
    return (a->grau() > b->grau());
}

//Algoritmo Guloso
void Metodo::Guloso(){
    resetaGrafo();
    vector<No*> g = grafo; //Fazendo a cópia do grafo
    sumInterferencia = 0;

    sort(g.begin(), g.end(), algoritmoOrdenacao); //Ordenando as arestas

    while(g.size() > 0){
        No* no = g.at(0);

        sumInterferencia += selecionaFrequencia(no);

        g.erase(g.begin());
    }
}

//Algoritmo do Guloso Randomizado
float Metodo::GulosoRandomizado(double alfaR){
    resetaGrafo();
    vector<No*> g = grafo; //Fazendo a cópia do grafo
    sumInterferencia = 0;

    sort(g.begin(), g.end(), algoritmoOrdenacao); //Ordenando as arestas

    while(g.size() > 0){
        int select = 0;
        if(g.size() != 1) {
            int maximo = (int)(g.size() * alfaR);
            if(maximo != 0)
                select = rand() % maximo;
        }

        No* no = g.at(select);

        sumInterferencia += selecionaFrequencia(no);

        g.erase(g.begin() + select);
    }

    //Salvando o melhor
    if(sumMenorInterferencia == -1 || sumInterferencia < sumMenorInterferencia) {
        sumMenorInterferencia = sumInterferencia;
        grafoFrequencias.clear();
        for(int i = 0; i < grafo.size(); i++)
            grafoFrequencias.push_back(grafo.at(i)->frequencia);
    }

    return sumInterferencia;
}

//Algoritmo do Guloso Randomizado
void Metodo::GulosoRandomizado(double alfaR, int itTotal){
    for(int i = 0; i < itTotal; i++)
        GulosoRandomizado(alfaR);
}

//Algoritmo Guloso Randomizado Reativo
void Metodo::GulosoRandomizadoReativo(int alfaRR, int betaRR, int gammaRR, int itTotal){
    double **alfas = new double*[alfaRR]; //Alocando o vetor dos alfas

    //Criando os alfas baseado na quantidade passada (alfaRR)
    for(int i = 0; i < alfaRR; i++){
        alfas[i] = new double[4];
        alfas[i][0] = (1.0/alfaRR) * (i + 1.0);
        alfas[i][1] = 1.0/alfaRR;               //
        alfas[i][2] = 0;                        //Somas das interferencias
        alfas[i][3] = 0;                        //Quantidade de execuções
    }

    int a, sum, ind = 0;
    //Executando cada iteração
    for(int it = 0; it < itTotal; it++){
        a = 0;
        sum = 0;
        if((it + 1) % gammaRR == 0 && it != 0){ // Atualizando as probabilidades a cada gammaRR
            for(int i = 0; i < alfaRR; i++){
                double qi, qj = 0;
                if(alfas[i][3] != 0){
                    qi = (sumMenorInterferencia/(alfas[i][2]/alfas[i][3]));
                    for(int j = 0; j < alfaRR; j++){
                        if(alfas[j][3] != 0)
                            qj += (sumMenorInterferencia/(alfas[j][2]/alfas[j][3]));
                    }
                }
                else{
                    qi = 0;
                    qj = 1;
                }

                alfas[i][1] = qi / (double)qj;
            }
        }

        if((it + 1) % betaRR == 0 || it == 0){ // Selecionando qual alfa usar a cada betaRR
            a = rand() % (101);
            sum = 0;
            for(int j = 0; j < alfaRR; j++){
                sum += (alfas[j][1] * 100);
                if(sum >= a){
                    ind = j;
                    break;
                }
            }
        }

        //Executando o Guloso Randomizado com o Alfa escolhido
        float cost = GulosoRandomizado(alfas[ind][0]);
        alfas[ind][2] += cost;
        alfas[ind][3]++;
    }

    cout << "Informacoes dos alfas: \n";
    cout << "[id] [Valor do Alfa] [Probabilidade Escolha] [Somatorio de Custos das Execucoes] [Quantidade de Execucoes]\n";
    for(int i = 0; i < alfaRR; i++){
        cout << i + 1 << " [" << alfas[i][0] << "] [" << alfas[i][1] << "] [" << alfas[i][2] << "] [" << alfas[i][3] << "]\n";
    }
}
