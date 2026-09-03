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

bool compararPorNos(int r, const int& a, const int& b);

#endif
