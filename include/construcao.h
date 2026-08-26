#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "solution.h"
// precisa do solution aqui porque tem definido um retorno de função com Solution, logo precisa saber
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_set>
#include <iostream>

using namespace std;

typedef struct InsertionInfo {
    int noInserido;
    int arestaRemovida;
    double custo;
}InsertionInfo;

Solution Construcao();
vector<InsertionInfo> calcularCustoInsercao(Solution& s, vector<int>& CL);
void escolherNosAleatorios(Solution& s, int tam);
vector<int> nosRestantes(const vector<int>& sequencia);
void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao);
void inserirNaSolucao(Solution& s, InsertionInfo selecionado);

bool compararPorCusto(const InsertionInfo& a, const InsertionInfo& b);

#endif
