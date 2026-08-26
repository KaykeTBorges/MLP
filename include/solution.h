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

    std::vector<Subsequence> prefix;
    std::vector<Subsequence> sufix;

    
    Solution(std::vector<int> route, double cost): route(route), cost(cost), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)) {}
    Solution() :  route(std::vector<int>(Data::getInstance().n + 1)), cost(0), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)), prefix(Data::getInstance().n + 1), sufix(Data::getInstance().n + 1) {}
    Solution(const Solution &s) : route(s.route), cost(s.cost), subseq_matrix(s.subseq_matrix), prefix(s.prefix), sufix(s.sufix) {}
    Solution(int lixo) : route(), cost(0), subseq_matrix(Data::getInstance().n + 1, std::vector<Subsequence>(Data::getInstance().n + 1)), prefix(Data::getInstance().n + 1), sufix(Data::getInstance().n + 1) { route.reserve(Data::getInstance().n + 1); }

    void buildTrivial();

    void print();

    void copy(const Solution &other);

    double evaluateSwap2(const int i, const int j);
    void swap2(const int i, const int j);

    double evaluateSwap(const int i, const int j, const Subsequence& miolo);
    double evaluateOpt2(const int i, const int j, const Subsequence& miolo);
    double evaluateReinsertion(const int i, const int j, const Subsequence& miolo);
    double evaluateOrOpt2(const int i, const int j, const Subsequence& miolo);
    double evaluateOrOpt3(const int i, const int j, const Subsequence& miolo);

    void swap(const int i, const int j, const Subsequence& miolo);
    void Opt2(const int i, const int j, const Subsequence& miolo);
    void Reinsertion(const int i, const int j, const Subsequence& miolo);
    void OrOpt2(const int i, const int j, const Subsequence& miolo);
    void OrOpt3(const int i, const int j, const Subsequence& miolo);

    double evaluateOrOptGeral(const int i, const int j, const int k);

    void pertubationDoubleBridgeTamanho();
    void pertubationNTamanho(const int qtdCortes);

    void UpdateSubseqSwap(const int i, const int j);
    void UpdateSubseq2Opt(const int i, const int j);
    void UpdateSubseqIJ(const int i, const int j);
    void UpdateLinear();
    void UpdateLinearIJ(const int i, const int j);

    Solution ILS(int maxIter, int maxIterIls);
};

#endif
