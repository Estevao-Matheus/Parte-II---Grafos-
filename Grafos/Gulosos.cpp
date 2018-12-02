#include "Gulosos.h"

Gulosos::Gulosos(string stringArq) {
    fstream arq;
    erro = false;

    try{
        arq.open(stringArq.c_str());
        if(arq.is_open()){
            arq >> n;
            grafo = vector<Vertice*>(n);

            for(int i = 0; i < n; i++)
                grafo.at(i) = new Vertice(i+1);

                  //Leitura de arestas
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
        cout << "O Arquivo se encontra  fora do padrao!" << endl;
        erro = true;
    }
}

//Imprime o Grafo na tela
void Gulosos::imprimeGrafo(vector<Vertice*> g){
    cout << "Grafo:\n";
    for(int i = 0; i < g.size(); i++){
        cout << "- " << g.at(i)->id << " [freqencia:" << g.at(i)->frequencia << "] -> ";
        for(int j = 0; j < g.at(i)->adj.size(); j++){
            cout << "[" << g.at(i)->adj.at(j)->id << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

//Função para resetar o Grafo
void Gulosos::resetaGrafo(){
    for(int i = 0; i < grafo.size(); i++)
        grafo.at(i)->frequencia = 0;
}
vector<Vertice*> Gulosos::getMelhorGrafo(){
    if(grafoFrequencias.size() > 0) {
        for(int i = 0; i < grafoFrequencias.size(); i++)
            grafo.at(i)->frequencia = grafoFrequencias.at(i);
    }

    return grafo;
}

//Função para ver a interferência
float Gulosos::getInterferencia(int frequencia1, int frequencia2){
    return interferencia[((frequencia1-1)*14)+(frequencia2-1)];
}

//Função para selecionar a Frequencia
float Gulosos::selecionaFrequencia(Vertice* no){
    int bestF;
    float bestInter;

    for(int f = 1; f <= 14; f++) {
        float interSomatorio = 0.0;

        for(Vertice* adj: no->adj) {
            if(adj->frequencia == 0)
                continue;

            interSomatorio += getInterferencia(f, adj->frequencia);
        }

        if(f == 1 || interSomatorio <= bestInter) {
            bestF = f;
            bestInter = interSomatorio;
        }
    }

    no->frequencia = bestF;
    return bestInter;
}

//Função auxiliar para a função e sort
bool Gulosos::algoritmoOrdenacao(Vertice* a, Vertice* b){
    return (a->grau() > b->grau());
}

//Algoritmo Guloso
void Gulosos::Guloso(){
    resetaGrafo();
    vector<Vertice*> g = grafo; //Fazendo a cópia do grafo
    somatorioInterferencia = 0;

    sort(g.begin(), g.end(), algoritmoOrdenacao); //Ordenando as arestas

    while(g.size() > 0){
        Vertice* no = g.at(0);

        somatorioInterferencia += selecionaFrequencia(no);

        g.erase(g.begin());
    }
}

//Algoritmo Guloso Randomizado
float Gulosos::GulosoRandomizado(double alfaR){
    resetaGrafo();
    vector<Vertice*> g = grafo; //Faz copia do grafo
    somatorioInterferencia = 0;

    sort(g.begin(), g.end(), algoritmoOrdenacao); //Ordena as arestas

    while(g.size() > 0){
        int select = 0;
        if(g.size() != 1) {
            int maximo = (int)(g.size() * alfaR);
            if(maximo != 0)
                select = rand() % maximo;
        }

        Vertice* no = g.at(select);

        somatorioInterferencia += selecionaFrequencia(no);

        g.erase(g.begin() + select);
    }

    //Salvando o melhor
    if(somatorioMenorInterferencia == -1 || somatorioInterferencia < somatorioMenorInterferencia) {
        somatorioMenorInterferencia = somatorioInterferencia;
        grafoFrequencias.clear();
        for(int i = 0; i < grafo.size(); i++)
            grafoFrequencias.push_back(grafo.at(i)->frequencia);
    }

    return somatorioInterferencia;
}

//Algoritmo Guloso Randomizado
void Gulosos::GulosoRandomizado(double alfaR, int itTotal){
    for(int i = 0; i < itTotal; i++)
        GulosoRandomizado(alfaR);
}

//Algoritmo Guloso Randomizado Reativo
void Gulosos::GulosoRandomizadoReativo(int alfaRR, int betaRR, int gammaRR, int itTotal){
    double **alfas = new double*[alfaRR]; //Alocando o vetor dos alfas

    //Criando os alfas baseado na quantidade passada (alfaRR)
    for(int i = 0; i < alfaRR; i++){
        alfas[i] = new double[4];
        alfas[i][0] = (1.0/alfaRR) * (i + 1.0);
        alfas[i][1] = 1.0/alfaRR;               //
        alfas[i][2] = 0;                        //Somas das interferencias
        alfas[i][3] = 0;                        //Quantidade de execuções
    }

    int a, somatorio, ind = 0;
    //Executando cada iteração
    for(int it = 0; it < itTotal; it++){
        a = 0;
        somatorio = 0;
        if((it + 1) % gammaRR == 0 && it != 0){ // Atualiza as probabilidades a cada gammaRR
            for(int i = 0; i < alfaRR; i++){
                double qi, qj = 0;
                if(alfas[i][3] != 0){
                    qi = (somatorioMenorInterferencia/(alfas[i][2]/alfas[i][3]));
                    for(int j = 0; j < alfaRR; j++){
                        if(alfas[j][3] != 0)
                            qj += (somatorioMenorInterferencia/(alfas[j][2]/alfas[j][3]));
                    }
                }
                else{
                    qi = 0;
                    qj = 1;
                }

                alfas[i][1] = qi / (double)qj;
            }
        }

        if((it + 1) % betaRR == 0 || it == 0){ // Seleciona qual alfa usar a cada betaRR
            a = rand() % (101);
            somatorio = 0;
            for(int j = 0; j < alfaRR; j++){
                somatorio += (alfas[j][1] * 100);
                if(somatorio >= a){
                    ind = j;
                    break;
                }
            }
        }

        //Executa o Guloso Randomizado com o Alfa escolhido
        float cost = GulosoRandomizado(alfas[ind][0]);
        alfas[ind][2] += cost;
        alfas[ind][3]++;
    }

    cout << "Informacoes dos alfas: \n";
    cout << "[id] [Valor de Alfa] [Probabilidade de Escolha] [Somatorio de Custos das Execucoes] [Quantidade de Execucoes]\n";
    for(int i = 0; i < alfaRR; i++){
        cout << i + 1 << " [" << alfas[i][0] << "] [" << alfas[i][1] << "] [" << alfas[i][2] << "] [" << alfas[i][3] << "]\n";
    }
}
