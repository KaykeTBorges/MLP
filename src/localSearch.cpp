#include "localSearch.h"
#include "perturbation.h"
#include "construcao.h"
#include "random.h"

void RVND(Solution &s){

    std::vector<int> NL = {1, 2, 3, 4, 5};  // NL = {1, 2, 3, 4} após implementar os movimentos de vizinhança
    bool improved = false;

    while(NL.empty() == false){
        int n = Random::getInt(0, static_cast<int>(NL.size()) - 1);

        switch(NL[n]){
            case 1:
                improved = bestImprovementSwap(s);
                break;
            case 2:
                improved = bestImprovmentOrOpt2(s);
                break;
            case 3:
                improved = bestImprovmentReinsertion(s);
                break;
            case 4:
                improved = bestImprovmentOrOpt3(s);
                break;
            case 5:
                improved = bestImprovmentOpt2(s);
                break;
            default:
                break;
        }

        if (improved){
        NL = {1, 2, 3, 4, 5}; // NL = {1, 2, 3, 4} após implementar os movimentos de vizinhança
        }

        else{
            NL.erase(NL.begin() + n);
        }
    
    }
}

bool bestImprovementSwap(Solution &s){
    Data & data = Data::getInstance();
    double delta, bestDelta = 0.0;
    Subsequence bestMiolo;
    int bestI, bestJ, i, j;
    bool improved = false;

    
    for (i = 1; i < data.n - 1; i++){
        Subsequence miolo;
        // não dá pra fazer sem um booleano, porque a concatenação iria atrapalhar nesse sentido
        // meu pensamento inicial era concatenar um miolo vazio com J, porém isso geraria o cálculo de todo jeito
        bool mioloVazio = true;
        for(j = i + 1; j < data.n; j++){
            delta = s.evaluateSwap(i, j, miolo);
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                bestMiolo = miolo;
                improved = true;
            }
            Subsequence no_j;
            no_j.W = 1; no_j.C = 0; no_j.T = 0;
            no_j.first = no_j.last = s.route[j];

            if(mioloVazio){
                miolo = no_j;
                mioloVazio = false;
            }else{
                miolo = Subsequence::Concatenate(miolo, no_j);
            }
        }
    }

    if(improved){
        s.swap(bestI, bestJ, bestMiolo);
    }

    return improved;
}

bool bestImprovmentOpt2(Solution &s){
    Data & data = Data::getInstance();
    double delta, bestDelta = 0.0;
    Subsequence bestMiolo;
    int bestI, bestJ, i, j;
    bool improved = false;

    // aqui o for do (i) precisa começar no 1, porque não pode mexer no inicial
    // e precisa ir até o n-2 porque não pode chegar no n-1 porque se não trocaria o final, que não pode
    for (i = 1; i < data.n - 2; i++){
        // o (j) tem que começar no i+2 porque ele não pode entrar dentro do bloco que vai ser transferido
        Subsequence miolo;
        // não dá pra fazer sem um booleano, porque a concatenação iria atrapalhar nesse sentido
        // meu pensamento inicial era concatenar um miolo vazio com J, porém isso geraria o cálculo de todo jeito
        bool mioloVazio = true;
        for(j = i + 1; j < data.n; j++){
            delta = s.evaluateOpt2(i, j, miolo);
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                bestMiolo = miolo;
                improved = true;
            }
            Subsequence no_j;
            no_j.W = 1; no_j.C = 0; no_j.T = 0;
            no_j.first = no_j.last = s.route[j];

            if(mioloVazio){
                miolo = no_j;
                mioloVazio = false;
            }else{
                miolo = Subsequence::Concatenate(no_j, miolo);
            }
        }
    }
    if(improved){
        s.Opt2(bestI, bestJ, bestMiolo);
    }

    return improved;
}

bool bestImprovmentReinsertion(Solution &s){
    Data & data = Data::getInstance();
    double delta, bestDelta = 0.0;
    Subsequence bestMiolo;
    int bestI, bestJ, i, j;
    bool improved = false;

    for (i = 1; i < data.n - 1; i++){
        Subsequence miolo;
        bool mioloVazio = true;
        for(j = i + 1; j < data.n; j++){
            delta = s.evaluateReinsertion(i, j, miolo);
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                bestMiolo = miolo;
                improved = true;
            }
            Subsequence no_j;
            no_j.W = 1; no_j.C = 0; no_j.T = 0;
            no_j.first = no_j.last = s.route[j];

            if(mioloVazio){
                miolo = no_j;
                mioloVazio = false;
            }else{
                miolo = Subsequence::Concatenate(miolo, no_j);
            }
        }
    }
    if(improved){
        s.Reinsertion(bestI, bestJ, bestMiolo);
    }

    return improved;
}

bool bestImprovmentOrOpt2(Solution &s){
    Data & data = Data::getInstance();
    double delta, bestDelta = 0.0;
    Subsequence bestMiolo;
    int bestI, bestJ, i, j;
    bool improved = false;

    // aqui o for do (i) precisa começar no 1, porque não pode mexer no inicial
    // e precisa ir até o n-2 porque não pode chegar no n-1 porque se não trocaria o final, que não pode
    for (i = 1; i < data.n - 2; i++){
        // o (j) tem que começar no i+2 porque ele não pode entrar dentro do bloco que vai ser transferido
        Subsequence miolo;
        // não dá pra fazer sem um booleano, porque a concatenação iria atrapalhar nesse sentido
        // meu pensamento inicial era concatenar um miolo vazio com J, porém isso geraria o cálculo de todo jeito
        bool mioloVazio = true;
        for(j = i + 2; j < data.n; j++){
            delta = s.evaluateOrOpt2(i, j, miolo);
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                bestMiolo = miolo;
                improved = true;
            }
            Subsequence no_j;
            no_j.W = 1; no_j.C = 0; no_j.T = 0;
            no_j.first = no_j.last = s.route[j];

            if(mioloVazio){
                miolo = no_j;
                mioloVazio = false;
            }else{
                miolo = Subsequence::Concatenate(miolo, no_j);
            }
        }
    }
    if(improved){
        s.OrOpt2(bestI, bestJ, bestMiolo);
    }

    return improved;
}

bool bestImprovmentOrOpt3(Solution &s){
    Data & data = Data::getInstance();
    double delta, bestDelta = 0.0;
    Subsequence bestMiolo;
    int bestI, bestJ, i, j;
    bool improved = false;

    // aqui o for do (i) precisa começar no 1, porque não pode mexer no inicial
    // e precisa ir até o n-3 porque não pode chegar no n-1 nem no n-2 porque se não trocaria o final, que não pode
    for (i = 1; i < data.n - 3; i++){
        // o (j) tem que começar no i+3 porque ele não pode entrar dentro do bloco que vai ser transferido
        Subsequence miolo;
        bool mioloVazio = true;
        for(j = i + 3; j < data.n; j++){
            delta = s.evaluateOrOpt3(i, j, miolo);
            if(delta < bestDelta){
                bestDelta = delta;
                bestI = i;
                bestJ = j;
                bestMiolo = miolo;
                improved = true;
            }
            Subsequence no_j;
            no_j.W = 1; no_j.C = 0; no_j.T = 0;
            no_j.first = no_j.last = s.route[j];

            if(mioloVazio){
                miolo = no_j;
                mioloVazio = false;
            }else{
                miolo = Subsequence::Concatenate(miolo, no_j);
            }
        }
    }
    if(improved){
        s.OrOpt3(bestI, bestJ, bestMiolo);
    }

    return improved;
}


Solution solve(){
    // Criamos uma instancia vazia de Solution apenas para poder invocar o método ILS
    Solution s;
    s.buildTrivial();
    std::cout << "Solucao inicial:" << std::endl;
    s.print();
    std::cout << "Solucao final:" << std::endl;
    int i_max = 10;
    int i_ils = std::min(100, Data::getInstance().n);
    
    // Aqui chamamos o ILS com os parâmetros do kit
    s = s.ILS(i_max, i_ils);
    
    return s;
}
