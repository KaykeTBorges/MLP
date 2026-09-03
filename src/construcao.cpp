#include "construcao.h"
#include "random.h"
#include "subsequence.h"

Solution Construcao(){
    Data & data = Data::getInstance();
    Solution s = Solution(0);
    s.route.push_back(1);

    std::vector<int> CL(data.n - 1);
    std::iota(CL.begin(), CL.end(), 2);

    double alpha = Random::getInt(0, 25) / 100;

    int r = 1;

    while(!CL.empty()){
        std::sort(CL.begin(), CL.end(), [&](int a, int b){return compararPorNos(r, a, b);});
        
        int selecionado = Random::getInt(0, (int) ceil(alpha * CL.size()));

        int c = CL[selecionado];

        s.route.push_back(c);

        r = c;
        
        // Remove o nó inserido da lista de candidatos
        CL.erase(CL.begin() + selecionado);
    }

    s.route.push_back(1);

    s.UpdateSubseqIJ(0, data.n);
    s.cost = s.subseq_matrix[0][Data::getInstance().n].C;
    return s;
}

bool compararPorNos(int r, const int& a, const int& b){
    Data & data = Data::getInstance();
    return data.matrizAdj[r][a] < data.matrizAdj[r][b];
}