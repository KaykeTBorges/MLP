#include "subsequence.h"
#include "solution.h"
#include "data.h"

void UpdateAllSubseq(Solution *s){
        Data & data = Data::getInstance();

        int n = data.n + 1;

        for(int i = 0; i < n; i++){
            s->subseq_matrix[i][i].W = (i > 0);
            s->subseq_matrix[i][i].C = 0;
            s->subseq_matrix[i][i].T = 0;
            s->subseq_matrix[i][i].first = s->route[i];
            s->subseq_matrix[i][i].last = s->route[i];

        }
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                s->subseq_matrix[i][j] = Subsequence::Concatenate(s->subseq_matrix[i][j-1], s->subseq_matrix[j][j]);
            }
        }

                    
        // subsequencias invertidas
        // (necessarias para o 2-opt)
        for (int i = n - 1; i >= 0; i--){
            for (int j = i - 1; j >= 0; j--){
                s->subseq_matrix[i][j] = Subsequence::Concatenate(s->subseq_matrix[i][j+1], s->subseq_matrix[j][j]);
            }
        }
}

void Solution::UpdateSubseqSwap(const int i, const int j){
    Data & data = Data::getInstance();

    int n = data.n;

    std::swap(subseq_matrix[i][i], subseq_matrix[j][j]);

    // aqui é até J por conta do condição, o a tem que ser <= j, logo não faz sentido ir além dele
    // só imaginar num intervalo, onde se comerçarmos no j, vai ser claro que não teremos o valor i nesse intervalo
    // visto que o i é menor que o j
    for(int a = 0; a <= j; a++){
        for(int b = a + 1; b <= data.n; b++){

            // o intervalo que contém i ou j precisa ser modificado
            bool update = (a <= i && b >= i) || (a <= j && b >= j);

            if(!update) continue;

            // só explicando aqui que não tinha entendido
            // aqui é a posição exemplo: a = 1 b = 3 logo intervalo de 1->3 
            // quer ser mudado, então vou de 1->2 e insiro o valor de 3, que é o b b
            subseq_matrix[a][b] = Subsequence::Concatenate(subseq_matrix[a][b-1], subseq_matrix[b][b]);
        }
    }

    // atualizar a parte invertida
    // aqui tem que sempre ser maior que j, é a condição para o b
    for(int b = i; b <= data.n; b++){
        // aqui é o b, precisa ser menor que o b porque é invertido
        for(int a = b - 1; a >= 0; a--){

            // o b aqui precisa ser maior que i logo por isso a gente começa o for dizendo que b é igual a i
            // porque se ele for menor nem entra no update
            // antes eu tinha usado o J mas ai ele estaria suprindo a condição, mas estaria excluindo algumas outras
            bool update = (a <= i && b >= i) || (a <= j && b >= j);

            if(!update) continue;
            
            subseq_matrix[b][a] = Subsequence::Concatenate(subseq_matrix[b][a+1], subseq_matrix[a][a]);
        }
    }
}

void Solution::UpdateSubseq2Opt(const int i, const int j){
    Data & data = Data::getInstance();

    int esquerda = i;
    int direita = j;

    // eu precisava atualizar os pontos iguais, e para não fazer igual ao updateAll que faz as operações sobre todos
    while(esquerda < direita){
        std::swap(subseq_matrix[esquerda][esquerda], subseq_matrix[direita][direita]);
        esquerda++;
        direita--;
    }


    for(int a = 0; a <= j; a++){
        for(int b = a + 1; b <= data.n; b++){

            bool update = (a <= i && b >= i) || (a <= j && b >= j);

            if(!update) continue;

            subseq_matrix[a][b] = Subsequence::Concatenate(subseq_matrix[a][b-1], subseq_matrix[b][b]);

        }
    }

    for(int b = i; b <= data.n; b++){
        for(int a = b - 1; a >= 0; a--){
            
            bool update = (a <= i && b >= i) || (a <= j && b >= j);
            
            if(!update) continue;

            subseq_matrix[b][a] = Subsequence::Concatenate(subseq_matrix[b][a+1], subseq_matrix[a][a]);
        }
    }
}

void Solution::UpdateSubseqIJ(const int i, const int j){
    Data & data = Data::getInstance();

    for(int k = 0; k <= data.n; k++){
            subseq_matrix[k][k].W = (k > 0);
            subseq_matrix[k][k].C = 0;
            subseq_matrix[k][k].T = 0;
            subseq_matrix[k][k].first = route[k];
            subseq_matrix[k][k].last = route[k];

    }

    for(int a = 0; a <= j; a++){
        for(int b = a + 1; b <= data.n; b++){

            int min_idx = std::min(i, j);
            int max_idx = std::max(i, j);
            bool update = (a <= max_idx && b >= min_idx);

            if(!update) continue;

            subseq_matrix[a][b] = Subsequence::Concatenate(subseq_matrix[a][b-1], subseq_matrix[b][b]);
        }
    }

    // atualizar a parte invertida
    for(int b = i; b <= data.n; b++){
        for(int a = b - 1; a >= 0; a--){

            int min_idx = std::min(i, j);
            int max_idx = std::max(i, j);
            bool update = (a <= max_idx && b >= min_idx);

            if(!update) continue;
            
            subseq_matrix[b][a] = Subsequence::Concatenate(subseq_matrix[b][a+1], subseq_matrix[a][a]);
        }
    }
}