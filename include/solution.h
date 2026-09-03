#ifndef SOLUTION_H
#define SOLUTION_H


#include "data.h"
// O include do localSearch.h foi removido daqui para evitar dependência circular
// Ele foi movido para o solution.cpp porque a classe Solution não precisa saber dele no header
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "subsequence.h"

struct Solution
{
    std::vector<int> route;
    double cost;
    std::vector<std::vector<Subsequence>> subseq_matrix;
    
    
    Solution(std::vector<int> route, double cost): route(route), cost(cost), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)) {}
    Solution() :  route(std::vector<int>(Data::getInstance().n + 1)), cost(0), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)) {}
    Solution(const Solution &s) : route(s.route), cost(s.cost), subseq_matrix(s.subseq_matrix) {}
    Solution(int lixo) : route(), cost(0), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)) { route.reserve(Data::getInstance().n + 1); }

    void buildTrivial();

    void print();

    void copy(const Solution &other);

    double evaluateSwap2(const int i, const int j);
    void swap2(const int i, const int j);

    double evaluateSwap(const int i, const int j);
    double evaluateOpt2(const int i, const int j); 
    double evaluateReinsertion(const int i, const int j);
    double evaluateOrOpt2(const int i, const int j);
    double evaluateOrOpt3(const int i, const int j);

    void swap(const int i, const int j);
    void Opt2(const int i, const int j);   
    void Reinsertion(const int i, const int j);
    void OrOpt2(const int i, const int j);
    void OrOpt3(const int i, const int j);

    double evaluateOrOptGeral(const int i, const int j, const int k);

    void pertubationDoubleBridgeTamanho();
    void pertubationNTamanho(const int qtdCortes);

    void UpdateSubseqSwap(const int i, const int j);
    void UpdateSubseq2Opt(const int i, const int j);
    void UpdateSubseqIJ(const int i, const int j);

    Solution ILS(int maxIter, int maxIterIls);
};

#endif
