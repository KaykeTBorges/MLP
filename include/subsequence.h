#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include "data.h"

struct Subsequence {
    double T; // tempo / distancia para percorrer toda essa subsequencia
    double C; // custo aculado dos nós, em relação a latencia
    int W; // numero de clientes
    int first, last;

    inline static Subsequence Concatenate(const Subsequence &sigma_1, const Subsequence &sigma_2) {
        Data & data = Data::getInstance();
        Subsequence sigma;
        double ligacao = data.matrizAdj[sigma_1.last][sigma_2.first]; // aqui acontece a ligação entre subsequencia, o final de uma começo de outra
        sigma.W = sigma_1.W + sigma_2.W; // soma da quantidade de nós em ambos, dá o valor final
        sigma.T = sigma_1.T + ligacao + sigma_2.T; // aqui é a soma de uma subsequencia com outra, porém lembrar de somar a ligação entre elas
        sigma.C = sigma_1.C + sigma_2.C + sigma_2.W * (sigma_1.T + ligacao); // todos a partir do primeiro do sigma2 vão receber o atraso de sigma1 completar
                                                                             // por isso soma a multiplicação da quantidade de nós do sigma2
        sigma.first = sigma_1.first;
        sigma.last = sigma_2.last;

        return sigma;
    }

}; 

void UpdateAllSubseq(struct Solution *s);

#endif
