#include "construcao.h"
#include "random.h"
#include "subsequence.h"


vector<InsertionInfo> calcularCustoInsercao(Solution& s, vector<int>& CL){
    Data & data = Data::getInstance();

    // O tamanho exato que precisaremos é (numero_de_arestas) * (candidatos)
    std::vector<InsertionInfo> custoInsercao((s.route.size() - 1) * CL.size());

    // pré calcula os tempos de chegada, latência acumulada até cada nó da rota atual
    std::vector<double> tempoChegada(s.route.size(), 0.0);
    for (size_t p = 1; p < s.route.size(); ++p) {
        tempoChegada[p] = tempoChegada[p-1] + data.matrizAdj[s.route[p-1]][s.route[p]];
    }

    int l = 0;
    for(int a = 0; a < s.route.size() - 1; a++){
        int i = a;
        int j = a+1;

        // quantos nós vem DEPOIS da inserção e sofrerão atraso
        int nos_afetados = s.route.size() - j;

        for(auto k : CL){
            // aqui é como se fosse o sigma_1
            //sigma.C = sigma_1.C + sigma_2.C + sigma_2.W * (sigma_1.T + ligacao);
            // delta_latencia = tempoChegada[i] + data.matrizAdj[s.route[i]][k] + (nos_afetados * delta_dist)

            // Aumento na distância física do trecho (T)
            double delta_dist = data.matrizAdj[s.route[i]][k] + data.matrizAdj[k][s.route[j]] 
                              - data.matrizAdj[s.route[i]][s.route[j]];
            
            // Tempo de chegada no novo nó (k)
            double tempo_k = tempoChegada[i] + data.matrizAdj[s.route[i]][k];
            
            // CUSTO MLP - a latência do novo nó + o atraso propagado aos nós da frente
            double delta_latencia = tempo_k + (nos_afetados * delta_dist);

            custoInsercao[l].custo = delta_latencia;
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
        
            l++;
        }
    }
    return custoInsercao;
}

Solution Construcao(){
    Solution s = Solution(0);
    escolherNosAleatorios(s, 3);
    std::vector<int> CL = nosRestantes(s.route);

    while(!CL.empty()){
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL);

        ordenarEmOrdemCrescente(custoInsercao);

        // Sorteia o alpha seguindo a base da literatura (R = {0.00, 0.01, ..., 0.25})
        double alpha = Random::getInt(0, 25) / 100.0;

        // ceil(alpha * tamanho)
        // O std::max entra aqui para impedir que o limite seja 0.
        int limite = std::max(1, (int)ceil(alpha * custoInsercao.size()));

        // Sorteia o candidato dentro do limite
        int selecionado = Random::getInt(0, limite - 1);

        inserirNaSolucao(s, custoInsercao[selecionado]);
        
        // Remove o nó inserido da lista de candidatos
        int noInserido = custoInsercao[selecionado].noInserido;
        CL.erase(std::remove(CL.begin(), CL.end(), noInserido), CL.end());
    }
    s.UpdateLinear();
    s.cost = s.prefix[Data::getInstance().n].C;
    return s;
}

void escolherNosAleatorios(Solution& s, int tam){
    Data & data = Data::getInstance();
    s.route.push_back(1);
    // usa unordered_set para garantir que não há nós duplicados na rota inicial
    std::unordered_set<int> inseridos;
    inseridos.insert(1); // o nó inicial já está na rota
    int i = 0;
    while(i < tam){
        int r = Random::getInt(2, data.n);
        if(inseridos.count(r) == 0){
            inseridos.insert(r);
            s.route.push_back(r);
            i++;
        }
    }
    s.route.push_back(1);
    // Calcula o custo inicial em Latência (MLP)
    s.cost = 0;
    double tempoChegada = 0;
    for(int i = 1; i < s.route.size(); i++){
        // o que vem antes na rota, até o posterior dele, soma os dois e dá o tempo de chegada naquele ponto
        // e por ser uma ideia de soma de prefixos
        tempoChegada += data.matrizAdj[s.route[i-1]][s.route[i]];
        s.cost += tempoChegada;
    }
}

std::vector<int> nosRestantes(const std::vector<int>& sequencia) {
    Data & data = Data::getInstance();

    // cria o vetor preenchido de 2 até data.n
    std::vector<int> restantes(data.n - 1);
    std::iota(restantes.begin(), restantes.end(), 2);
    
    // coloca a sequência em um Set para busca rápida O(1)
    std::unordered_set<int> para_remover(sequencia.begin(), sequencia.end());

    // remove eficientemente todos os elementos que estão na sequência
    restantes.erase(
        std::remove_if(restantes.begin(), restantes.end(), [&](int x) {
            return para_remover.count(x) > 0;
        }), 
        restantes.end()
    );

    // retorna o vetor modificado
    return restantes;
}

void inserirNaSolucao(Solution& s, InsertionInfo selecionado){
    Data & data = Data::getInstance();

    s.route.insert(s.route.begin() + selecionado.arestaRemovida + 1, selecionado.noInserido);
    s.cost += selecionado.custo;
}

void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao){
    std::sort(custoInsercao.begin(), custoInsercao.end(), compararPorCusto);
}

bool compararPorCusto(const InsertionInfo& a, const InsertionInfo& b){
    return a.custo < b.custo;
}
