#include "solution.h"
// O include foi movido para o .cpp de solution pois a função RVND só é de fato chamada na implementação do ILS
#include "localSearch.h"
// O include foi movido para o .cpp de solution pois a função Construcao só é de fato chamada na implementação do ILS
#include "construcao.h"

void Solution::print(){
    std::cout << "Route: ";
    for(int i = 0; i < Data::getInstance().n; i++){
        std::cout << route[i] << " - ";
    }
    std::cout << route[Data::getInstance().n] << std::endl;
    std::cout << "Latência Total (MLP Cost): " << cost << std::endl;
    std::cout << "Distância Percorrida: " << subseq_matrix[0][Data::getInstance().n].T << std::endl;
}

void Solution::copy(const Solution &other){
    route = std::vector<int>(other.route);
 cost = other.cost;
}




void Solution::buildTrivial(){
    Data & data = Data::getInstance();

    for(int i = 1; i <= data.n; i++){
        route[i-1] = i;
    }
    route[data.n] = 1;

    // popula a subseq_matrix para que print() e as funções de avaliação funcionem
    UpdateAllSubseq(this);

    // custo MLP (latência acumulada) derivado diretamente da matriz
    cost = subseq_matrix[0][data.n].C;
}


double Solution::evaluateSwap(const int i, const int j){
    Data & data = Data::getInstance();
    Subsequence final;

    if(j == i+1){
        Subsequence bloco1 = subseq_matrix[0][i-1];

        Subsequence bloco2 = subseq_matrix[j][j];
        Subsequence bloco3 = subseq_matrix[i][i];

        Subsequence bloco4 = subseq_matrix[j+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);

    }
    else{
        Subsequence bloco1 = subseq_matrix[0][i-1];
        // aqui é já com as posições mudadas
        Subsequence bloco2 = subseq_matrix[j][j];

        Subsequence bloco3 = subseq_matrix[i+1][j-1];

        Subsequence bloco4 = subseq_matrix[i][i];

        Subsequence bloco5 = subseq_matrix[j+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
        final = Subsequence::Concatenate(final, bloco5);

    }

    double delta = final.C - this->cost;

    return delta;

}

double Solution::evaluateOpt2(const int i, const int j){
    Data & data = Data::getInstance();

    Subsequence final;

    Subsequence bloco1 = subseq_matrix[0][i-1];
    // aqui dá certo porque a função updateALL faz o calculo do reverso
    // ai eu tenho definido, se fosse o básico normal, eu nunca teria essa informação
    // porque vai de i -> j
    Subsequence bloco2 = subseq_matrix[j][i];
    Subsequence bloco3 = subseq_matrix[j+1][data.n];

    final = Subsequence::Concatenate(bloco1, bloco2);
    final = Subsequence::Concatenate(final, bloco3);

    double delta = final.C - this->cost;

    return delta;

}

double Solution::evaluateReinsertion(const int i, const int j){
    Data & data = Data::getInstance();

    Subsequence final;

    if(j == i+1){
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[j][j];
        Subsequence bloco3 = subseq_matrix[i][i];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);   
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
    }else{
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[i+1][j];
        Subsequence bloco3 = subseq_matrix[i][i];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];
    
        final = Subsequence::Concatenate(bloco1, bloco2);   
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
    }
    double delta = final.C - this->cost;

    return delta;
}

double Solution::evaluateOrOpt2(const int i, const int j){
    Data & data = Data::getInstance();

    Subsequence final;

    // nesse código precisa ser garantido que o n é maior que 3, porque se não, pode dar segmentention fault
    if(j == i+2){
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[j][j];
        Subsequence bloco3 = subseq_matrix[i][i+1];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);

    }else{
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[i+2][j];
        Subsequence bloco3 = subseq_matrix[i][i+1];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];


        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
        }

        double delta = final.C - this->cost;

        return delta;
}

double Solution::evaluateOrOpt3(const int i, const int j){
    Data & data = Data::getInstance();
    
    Subsequence final;
    
    if(j == i+3){
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[j][j];
        Subsequence bloco3 = subseq_matrix[i][i+2];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);

    }else{
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[i+3][j];
        Subsequence bloco3 = subseq_matrix[i][i+2];
        Subsequence bloco4 = subseq_matrix[j+1][data.n];


        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
        }

        double delta = final.C - this->cost;


    return delta;
}

// double evaluateOrOptGeral(const int i, const int j, const int k){
//     Data & data = Data::getInstance();
//     double delta;

//     if(k == 1){
//         delta = evaluateReinsertion(i, j);
//     }else if(k == 2){
//         return 
//     }
// }

void Solution::swap(const int i, const int j){
    Data & data = Data::getInstance();
    // aqui eu poderia atribuir direto, mas para manter o mais igual eu fiz o valor final - o custo atual
    // porque após concatenar eu já descubro o valor final direto
    cost += evaluateSwap(i, j);  

    int aux = route[i];
    route[i] = route[j];
    route[j] = aux;
    UpdateSubseqIJ(i, j);
    
}

void Solution::Opt2(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateOpt2(i, j);

    // fim exclusivo
    std::reverse(route.begin() + i, route.begin() + (j + 1));
    UpdateSubseqIJ(i, j);
}

void Solution::Reinsertion(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateReinsertion(i, j);

    std::rotate(route.begin() + i, route.begin() + (i+1), route.begin() + (j+1));
    UpdateSubseqIJ(i, j);

}

void Solution::OrOpt2(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt2(i, j);

    // o primeiro valor é onde o bloco começa (i)
    // o segundo valor é o valor de proximo dele (i+2, porque queremos o bloco)
    // o terceiro valor é logo após o destino final (j+1)
    std::rotate(route.begin() + i, route.begin() + (i+2), route.begin() + (j+1));
    UpdateSubseqIJ(i, j+1);
}

void Solution::OrOpt3(const int i, const int j){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt3(i, j);

    std::rotate(route.begin() + i, route.begin() + (i+3), route.begin() + (j+1));
    UpdateSubseqIJ(i, j+2);

}

Solution Solution::ILS(int maxIter, int maxIterIls){
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;

    for (int i = 0; i < maxIter; i++) {
        Solution s = Construcao();  
        Solution best = s;
            
        int iterIls = 0;

        while(iterIls <= maxIterIls){
            RVND(s);
            if(s.cost < best.cost){
                best = s;
                iterIls = 0;
            }else{
                // aqui é porque o double bridge estava sendo aplicado na solução que tinha piorado
                // e não na solução melhor, que a best, então se o custo der maior, precisamos voltar ao melhor
                // e ai sim aplicar a perturbação
                s = best;
            }
            s.pertubationDoubleBridgeTamanho();
            iterIls++;
        }
        
        if(best.cost < bestOfAll.cost){
            bestOfAll = best;
        }
    }

    return bestOfAll;
}
