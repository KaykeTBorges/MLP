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
    std::cout << "Distância Percorrida: " << prefix[Data::getInstance().n].T << std::endl;
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

    UpdateLinear();
    cost = prefix[data.n].C;
}


double Solution::evaluateSwap(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    Subsequence no_i;
    no_i.W = 1; no_i.T = 0.0; no_i.C = 0.0;
    no_i.first = route[i]; no_i.last = route[i];

    Subsequence no_j;
    no_j.W = 1; no_j.T = 0.0; no_j.C = 0.0;
    no_j.first = route[j]; no_j.last = route[j];

    Subsequence final = prefix[i-1];
    final = Subsequence::Concatenate(final, no_j);

    if(j > i+1){
        // aqui tem um miolo a ser "somado" nessa concatenação
        final = Subsequence::Concatenate(final, miolo);
    }
    // senão não tem nenhum miolo, o j se encontra logo depois do i
    // ai eu posso manter sem else, porque já é o normal
    final = Subsequence::Concatenate(final, no_i);
    final = Subsequence::Concatenate(final, sufix[j+1]);
        
    double delta = final.C - this->cost;

    return delta;

}

double Solution::evaluateOpt2(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    Subsequence no_i;
    no_i.W = 1; no_i.T = 0.0; no_i.C = 0.0;
    no_i.first = route[i]; no_i.last = route[i];

    Subsequence no_j;
    no_j.W = 1; no_j.T = 0.0; no_j.C = 0.0;
    no_j.first = route[j]; no_j.last = route[j];

    Subsequence final = prefix[i-1];
    final = Subsequence::Concatenate(final, no_j);

    if(j > i + 1){
        final = Subsequence::Concatenate(final, miolo);
    }

    final = Subsequence::Concatenate(final, no_i);
    final = Subsequence::Concatenate(final, sufix[j+1]);

    double delta = final.C - this->cost;

    return delta;

}

double Solution::evaluateReinsertion(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    Subsequence no_i;
    no_i.W = 1; no_i.T = 0.0; no_i.C = 0.0;
    no_i.first = route[i]; no_i.last = route[i];

    Subsequence no_j;
    no_j.W = 1; no_j.T = 0.0; no_j.C = 0.0;
    no_j.first = route[j]; no_j.last = route[j];

    Subsequence final;

    if(j > i){
        final = prefix[i-1];
        if(j > i+1){
            final = Subsequence::Concatenate(final, miolo);
        }
        final = Subsequence::Concatenate(final, no_j);
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, sufix[j+1]);
    }else{
        final = prefix[j-1];
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, no_j);
        // aqui a lógica muda, porque o j vem antes
        // o miolo corresponde a partir j+1 até o i-1, só que o i-1 não entra na conversa
        // e o fim é inclusivo lá no loop de bestImprovement
        if(j+1 < i){
            final = Subsequence::Concatenate(final, miolo);
        }
        final = Subsequence::Concatenate(final, sufix[i+1]);
    }

    double delta = final.C - this->cost;

    return delta;
}

double Solution::evaluateOrOpt2(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    Subsequence node_a;
    node_a.W = (i > 0) ? 1 : 0; 
    node_a.T = 0.0; 
    node_a.C = 0.0;
    node_a.first = route[i]; 
    node_a.last = route[i];
    Subsequence node_b;
    node_b.W = 1; 
    node_b.T = 0.0; 
    node_b.C = 0.0;
    node_b.first = route[i+1]; 
    node_b.last = route[i+1];

    Subsequence no_i = Subsequence::Concatenate(node_a, node_b);

    Subsequence no_j;
    no_j.W = 1; no_j.T = 0.0; no_j.C = 0.0;
    no_j.first = route[j]; no_j.last = route[j];

    Subsequence final;

    if(j > i){
        final = prefix[i-1];
        // nesse código precisa ser garantido que o n é maior que 3, porque se não, pode dar segmentention fault
        if(j > i+2){
            final = Subsequence::Concatenate(final, miolo);
        }
        final = Subsequence::Concatenate(final, no_j);
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, sufix[j+1]);
    }else{
        final = prefix[j-1];
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, no_j);
        // aqui a lógica muda, porque o j vem antes
        // o miolo corresponde a partir j+1 até o i-1, só que o i-1 não entra na conversa
        // e o fim é inclusivo lá no loop de bestImprovement
        if(j+1 < i){
            final = Subsequence::Concatenate(final, miolo);
        }
        final = Subsequence::Concatenate(final, sufix[i+2]);
    }
    

    double delta = final.C - this->cost;

    return delta;
}

double Solution::evaluateOrOpt3(const int i, const int j, const Subsequence& miolo){
        Data & data = Data::getInstance();
    Subsequence node_a;
    node_a.W = (i > 0) ? 1 : 0; 
    node_a.T = 0.0; 
    node_a.C = 0.0;
    node_a.first = route[i]; 
    node_a.last = route[i];
    Subsequence node_b;
    node_b.W = 1; 
    node_b.T = 0.0; 
    node_b.C = 0.0;
    node_b.first = route[i+1]; 
    node_b.last = route[i+1];
    Subsequence node_c;
    node_c.W = 1; 
    node_c.T = 0.0; 
    node_c.C = 0.0;
    node_c.first = route[i+2]; 
    node_c.last = route[i+2];

    Subsequence no_i = Subsequence::Concatenate(node_a, node_b);
    no_i = Subsequence::Concatenate(no_i, node_c);

    Subsequence no_j;
    no_j.W = 1; no_j.T = 0.0; no_j.C = 0.0;
    no_j.first = route[j]; no_j.last = route[j];

    Subsequence final;

    if(j > i){
        final = prefix[i-1];
        // nesse código precisa ser garantido que o n é maior que 3, porque se não, pode dar segmentention fault
        if(j > i+3){
            final = Subsequence::Concatenate(final, miolo);

        }
        final = Subsequence::Concatenate(final, no_j);
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, sufix[j+1]);
    }else{
        final = prefix[j-1];
        final = Subsequence::Concatenate(final, no_i);
        final = Subsequence::Concatenate(final, no_j);
        // aqui a lógica muda, porque o j vem antes
        // o miolo corresponde a partir j+1 até o i-1, só que o i-1 não entra na conversa
        // e o fim é inclusivo lá no loop de bestImprovement
        if(j+1 < i){
            final = Subsequence::Concatenate(final, miolo);
        }
        final = Subsequence::Concatenate(final, sufix[i+3]);
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

void Solution::swap(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    // aqui eu poderia atribuir direto, mas para manter o mais igual eu fiz o valor final - o custo atual
    // porque após concatenar eu já descubro o valor final direto
    cost += evaluateSwap(i, j, miolo);  

    int aux = route[i];
    route[i] = route[j];
    route[j] = aux;
    UpdateLinearIJ(i, j);
    
}

void Solution::Opt2(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    cost += evaluateOpt2(i, j, miolo);

    // fim exclusivo
    std::reverse(route.begin() + i, route.begin() + (j + 1));
    UpdateLinearIJ(i, j);
}

/*
 * como o std::rotate funciona
 * 
 *  principio std::rotate(first, middle, last)
 * 
 * Regra geral do C++ divide o intervalo [first, last) (não inclusivo, no ultimo) em dois blocos:
 *   - Bloco 1: de 'first' ate 'middle-1'
 *   - Bloco 2: de 'middle' ate 'last-1'
 * O rotate simplesmente inverte a ordem dos blocos
 * O que era [Bloco 1, Bloco 2] passa a ser [Bloco 2, Bloco 1].
 * 
 * CASO 1: Mover os nos em 'i' para depois do 'j'
 * - first = inicio do no movido (i)
 * - middle = fim do no movido (ex i+1 para Reinsertion, i+2 para OrOpt2)
 * - last = fim do destino (j+1)
 * 
 *   Bloco 1 = os nos que queremos mover
 *   Bloco 2 = O "miolo" (nos que estao no meio do caminho)
 * Apos o rotate: O miolo vem para a esquerda, e o no movido cai no lugar certo a direita, na posicao j
 * 
 * CASO 2: Mover os nos em 'i' para a posicao 'j' (j sendo menor, vindo antes que i)
 * - first = posicao alvo de destino (j)
 * - middle = inicio do no que queremos mover (i)
 * - last = fim do no que queremos mover (ex i+1 para Reinsertion)
 * 
 *   Bloco 1 = O "miolo" (nos que agora estao antes do 'i')
 *   Bloco 2 = os nos que queremos mover
 * Apos o rotate: O no movido vem para a esquerda (para a posicao j), e o miolo vai para a direita
 */


void Solution::Reinsertion(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    cost += evaluateReinsertion(i, j, miolo);

    if(i <= j){
        std::rotate(route.begin() + i, route.begin() + (i+1), route.begin() + (j+1));
    }else{
        std::rotate(route.begin() + j, route.begin() + i, route.begin() + (i+1));
    }
    UpdateLinearIJ(i, j);
}

void Solution::OrOpt2(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt2(i, j, miolo);

    // o primeiro valor é onde o bloco começa (i)
    // o segundo valor é o valor de proximo dele (i+2, porque queremos o bloco)
    // o terceiro valor é logo após o destino final (j+1)
    if(i <= j){
        std::rotate(route.begin() + i, route.begin() + (i+2), route.begin() + (j+1));
        UpdateLinearIJ(i, j+1);
    }else{
        std::rotate(route.begin() + j, route.begin() + i, route.begin() + (i+2));
        UpdateLinearIJ(i+1, j);
    }
}

void Solution::OrOpt3(const int i, const int j, const Subsequence& miolo){
    Data & data = Data::getInstance();
    cost += evaluateOrOpt3(i, j, miolo);

    if(i <= j){
        std::rotate(route.begin() + i, route.begin() + (i+3), route.begin() + (j+1));
        UpdateLinearIJ(i, j+2);
    }else{
        std::rotate(route.begin() + j, route.begin() + i, route.begin() + (i+3));
        UpdateLinearIJ(i+2, j);
    }
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
                best.copy(s);
                best.UpdateLinear();
                iterIls = 0;

                 if (s.cost < bestOfAll.cost){
                    bestOfAll.copy(s);
                    bestOfAll.UpdateLinear();
                    
                 }   
            }else{
                // aqui é porque o double bridge estava sendo aplicado na solução que tinha piorado
                // e não na solução melhor, que a best, então se o custo der maior, precisamos voltar ao melhor
                // e ai sim aplicar a perturbação
                s.copy(best);
                s.UpdateLinear();
            }

            s.pertubationDoubleBridgeTamanho();
            iterIls++;
        }
        

    }

    return bestOfAll;
}
