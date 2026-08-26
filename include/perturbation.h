#ifndef PERTURBATION_H
#define PERTURBATION_H

#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

std::vector<int> perturbation2(const std::vector<int> routeOriginal);
std::vector<int> perturbationN(const std::vector<int> routeOriginal, const int qtdCortes);
std::vector<int> perturbation4(const std::vector<int> routeOrginal);
std::vector<int> pertubationDoubleBridge(const std::vector<int> routeOriginal);

// explicando a ideia que tive, primeiro pensei em fazer um corte em algum lugar dividindo em 3 blocos
// ai eu consigo tirar o que tava A > B > C transforma A > C > B mas percebi que não era isso a ser pedido, mas percebi que poderia melhorar isso
// essa divisão de blocos podiam gerar de uma forma N não necessitando de uma definição base minha
// dai que surgiu a ideia de pertubationN usa a mesma lógica da divisão em cortes que geram blocos = cortes + 1
// e a partir deles eu troco a ordem, dando um shuffle na ordem antes linear, agora bangunçada
// mas ainda assim não era o que era pedido, e o tamanho também não era respeitado
// primeiro implementei o double bridge pedido, mas ainda com o problema do tamanho sem ser respeitado
// o double bridge é o que troca segmentos de lugar
// agora garanti o tamanho no abaixo


#endif