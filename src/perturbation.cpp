#include "perturbation.h"
#include "solution.h"
#include "random.h"


std::vector<int> perturbation2(const std::vector<int> routeOriginal){
    Data & data = Data::getInstance();

    // dentro do intervalo que vai ser escolhido
    // foi tirado o 0 e n porque não podem ser tranferidos de posição

    std::vector<int> cortes;
    while(cortes.size() < 2){
        int pos = Random::getInt(1, data.n - 1);

        if(std::find(cortes.begin(), cortes.end(), pos) == cortes.end()){
            cortes.push_back(pos);
        }
    }
    int i = cortes[0];
    int j = cortes[1];

    std::vector<int> novaRoute;
    novaRoute.reserve(data.n+1);

    if(i > j){
        // j vem primeiro e i vem depois na ordem
        novaRoute.insert(novaRoute.end(), routeOriginal.begin(), routeOriginal.begin() + j);
        novaRoute.insert(novaRoute.end(), routeOriginal.begin() + i, routeOriginal.end());
        novaRoute.insert(novaRoute.end(), routeOriginal.begin() + j, routeOriginal.begin() + i);
    }else{
        novaRoute.insert(novaRoute.end(), routeOriginal.begin(), routeOriginal.begin() + i);
        novaRoute.insert(novaRoute.end(), routeOriginal.begin() + j, routeOriginal.end());
        novaRoute.insert(novaRoute.end(), routeOriginal.begin() + i, routeOriginal.begin() + j);
    }
    return novaRoute;
}

std::vector<int> perturbationN(const std::vector<int> routeOriginal, const int qtdCortes){
    Data & data = Data::getInstance();

    // dentro do intervalo que vai ser escolhido
    // foi tirado o 0 e n porque não podem ser tranferidos de posição

    std::vector<int> cortes;
    while(cortes.size() < qtdCortes){
        int pos = Random::getInt(1, data.n - 1);

        if(std::find(cortes.begin(), cortes.end(), pos) == cortes.end()){
            cortes.push_back(pos);
        }
    }

    std::sort(cortes.begin(), cortes.end());
    // [3, 7, 12, 15] -> tamanho máximo é 20 por exemplo
    // primeiro bloco (0) = 0 - 2
    // segundo bloco (1) = 3 - 7
    cortes.insert(cortes.begin(), 0);
    cortes.push_back(data.n);

    // foram qtdCortes + 1 dá o valor de blocos cortados
    // qtdCortes cortes geram qtdCortes + 1 blocos
    std::vector<int> ordemInsercao(qtdCortes + 1);
    // essa função cria no vetor valores de ordem crescente partindo de 0
    // então é 0, 1, 2, 3... baseado no tamanho definido acima
    std::iota(ordemInsercao.begin(), ordemInsercao.end(), 1);
    std::shuffle(ordemInsercao.begin(), ordemInsercao.end(), Random::gen());

    std::vector<int> novaRoute;
    novaRoute.reserve(data.n+1);

    // garante a inserção do começo
    novaRoute.insert(novaRoute.end(), routeOriginal.begin(), routeOriginal.begin() + cortes[1]);
    
    for(int indice : ordemInsercao){
        // aqui ele pega o os cortes já feitos em ordem baseado na ordem de inserção
        // porque os cortes são blocos dentro da rota, de tamanhos quaisquer
        // ai através do shuffle esses blocos que estavam em ordem vão ser inseridos de maneira aleatória
        // porque era minha dúvida de como poderia inserir de maneira aleatória, mas ai é só misturar o indices dos blocos
        // ai eu consigo agora inserir, o inicio é sempre o primeiro do indice em cortes, e garante que não quebra
        // porque o insert na novaRoute é sempre no final
        int inicio = cortes[indice];
        int fim = cortes[indice + 1];

        novaRoute.insert(novaRoute.end(), routeOriginal.begin() + inicio, routeOriginal.begin() + fim);
        // só um adendo que fui pesquisar, porque isso ia quebrar de alguma forma, porque ia duplicar os valores
        // mas o insert funciona em que, quando chega no route + fim, ele nunca vai até o fim, ele para -1 posição
        // então garante a não duplicação que era meu medo
        // e é isso que inserir o 0 e data.n no vetor de cortes tbm garante que eles estarão no novo vetor
        // é um limite superior não inclusivo -> exclusivo
    }
    // garante a inserção do fim
    novaRoute.insert(novaRoute.end(), routeOriginal.begin() + cortes[qtdCortes], routeOriginal.end());

    return novaRoute;
}

std::vector<int> perturbation4(const std::vector<int> routeOrginal){
    Data & data = Data::getInstance();

    // dentro do intervalo que vai ser escolhido
    // foi tirado o 0 e n porque não podem ser tranferidos de posição

    std::vector<int> cortes;
    while(cortes.size() < 3){
        int pos = Random::getInt(1, data.n - 1);

        if(std::find(cortes.begin(), cortes.end(), pos) == cortes.end()){
            cortes.push_back(pos);
        }
    }
    std::sort(cortes.begin(), cortes.end());

    int i = cortes[0];
    int j = cortes[1];
    int k = cortes[2];

    // inicio -> i = bloco A
    // i -> j = bloco B
    // j -> k = bloco C
    // k -> fim = bloco D

    // eu vou fazer esse mesmo código, mas para ter a variância dele, vou por um if
    // esse if não é necessário, mas garante umas diferenças
    // eu posso fazer várias variações, 24 anagramas, logo um shuffle como o de cima funciona melhor
    // if(cortes[0] % 2 == 0){
    //     // bloco A
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin(), routeOrginal.begin() + i);

    //     // bloco C
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + j, routeOrginal.begin() + k);

    //     // bloco B
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + i, routeOrginal.begin() + j);

    //     // bloco D
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + k, routeOrginal.end());
    // }else{
    //     // bloco C
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + j, routeOrginal.begin() + k);

    //     // bloco B
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + i, routeOrginal.begin() + j);

    //     // bloco A
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin(), routeOrginal.begin() + i);

    //     // bloco D
    //     novaRoute.insert(novaRoute.end(), routeOrginal.begin() + k, routeOrginal.end());
    // }

    cortes.insert(cortes.begin(), 0);
    cortes.push_back(data.n);

    // é 3 + 1, porque a quantidade de cortes + 1 gera os blocos, 3 cortes por exemplo, geram 4 blocos dentro da rota
    std::vector<int> ordemInsercao(3 + 1);
    std::iota(ordemInsercao.begin(), ordemInsercao.end(), 0);
    std::shuffle(ordemInsercao.begin(), ordemInsercao.end(), Random::gen());

    std::vector<int> novaRoute;
    novaRoute.reserve(data.n+1);
    
    for(int indice : ordemInsercao){
        int inicio = cortes[indice];
        int fim = cortes[indice + 1];

        novaRoute.insert(novaRoute.end(), routeOrginal.begin() + inicio, routeOrginal.begin() + fim);
    }

    

    return novaRoute;
}

std::vector<int> pertubationDoubleBridge(const std::vector<int> routeOriginal){
    Data & data = Data::getInstance();

    // int tMin = 2;
    // int tMax = ceil(V / 10);
    // bool valido = false;
    // while de valido, até encontrar um corte que esteja dentro desse válido
    // o problema seria a demora e o custo disso

    // dentro do intervalo que vai ser escolhido
    // foi tirado o 0 e n porque não podem ser tranferidos de posição

    std::vector<int> cortes;
    while(cortes.size() < 4){
        int pos = Random::getInt(1, data.n - 1);
        // tem que lembrar que aqui eu não garanto um tamanho minimo nem maximo

        if(std::find(cortes.begin(), cortes.end(), pos) == cortes.end()){
            cortes.push_back(pos);
        }
    }
    std::sort(cortes.begin(), cortes.end());

    int i = cortes[0];
    int j = cortes[1];
    int k = cortes[2];
    int l = cortes[3];

    std::vector<int> novaRoute;
    novaRoute.reserve(data.n+1);

    novaRoute.insert(novaRoute.end(), routeOriginal.begin(), routeOriginal.begin() + i);
    novaRoute.insert(novaRoute.end(), routeOriginal.begin() + k, routeOriginal.begin() + l);
    novaRoute.insert(novaRoute.end(), routeOriginal.begin() + j, routeOriginal.begin() + k);
    novaRoute.insert(novaRoute.end(), routeOriginal.begin() + i, routeOriginal.begin() + j);
    novaRoute.insert(novaRoute.end(), routeOriginal.begin() + l, routeOriginal.end());

    return novaRoute;
}

void Solution::pertubationDoubleBridgeTamanho(){
    Data & data = Data::getInstance();

    int tMin = 2;
    int tMax = ceil(data.n / 10.0);

    // esses tamanhos são para definir os tamanhos dos segmentos, quais serão seus tamanhos
    int tamanho_1 = Random::getInt(tMin, tMax);
    int tamanho_2 = Random::getInt(tMin, tMax);

    // o tamanho maximo de I é para que o primeiro indice não ultrapasse o tamanho do vetor de rota
    // garantindo também que o final do segundo segmento não mova o depósito final (posição data.n)
    int tamanhoMaximoPrimeiroSegmento = data.n - tamanho_1 - tamanho_2 - 2;

    // aqui defini o inicio do primeiro segmento, não pode ser (0), porque o inicio não pode ser movido
    int i = Random::getInt(1, tamanhoMaximoPrimeiroSegmento);
    // o resto do seu segmento é o ponto inicial mais o seu tamanho anteriormente definido
    int j = i + tamanho_1;

    // aqui é o segundo segmento definido, pode começar logo depois de j + 1 para que não ocorra sobreposição
    // e o máximo é até o tamanho total - 1 -> para evitar mover o depósito final
    int tamanhoMinimoSegundoSegmento = j + 1;
    int tamanhoMaximoSegundoSegmento = data.n - tamanho_2 - 1;

    // mesmo funcionamento de i e do j
    int k = Random::getInt(tamanhoMinimoSegundoSegmento, tamanhoMaximoSegundoSegmento);
    int l = k + tamanho_2;

    std::vector<int> novaRoute;
    novaRoute.reserve(data.n);

    Subsequence final;

    if(k == j + 1){
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[k][l];
        Subsequence bloco3 = subseq_matrix[i][j];
        Subsequence bloco4 = subseq_matrix[l+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);

    }else{
        Subsequence bloco1 = subseq_matrix[0][i-1];
        Subsequence bloco2 = subseq_matrix[k][l];
        Subsequence bloco3 = subseq_matrix[j+1][k-1];
        Subsequence bloco4 = subseq_matrix[i][j];
        Subsequence bloco5 = subseq_matrix[l+1][data.n];

        final = Subsequence::Concatenate(bloco1, bloco2);
        final = Subsequence::Concatenate(final, bloco3);
        final = Subsequence::Concatenate(final, bloco4);
        final = Subsequence::Concatenate(final, bloco5);
    }

    cost = final.C;

    novaRoute.insert(novaRoute.end(), route.begin(), route.begin() + i);
    novaRoute.insert(novaRoute.end(), route.begin() + k, route.begin() + l+1);
    novaRoute.insert(novaRoute.end(), route.begin() + j+1, route.begin() + k);
    novaRoute.insert(novaRoute.end(), route.begin() + i, route.begin() + j+1);
    novaRoute.insert(novaRoute.end(), route.begin() + l+1, route.end());

    route = std::move(novaRoute);
    // recalcula toda a subseq_matrix pois a rota foi reorganizada
    UpdateAllSubseq(this);
}

void Solution::pertubationNTamanho(const int qtdCortes){
    Data & data = Data::getInstance();

    int tamMin = 2;
    int tamMax = ceil(data.n / 10.0);

    // só o miolo, não pega o fim
    int restante = data.n - 1;

    // vetor de cortes guarda as posições que delimitam os bloco
    // inicial e final (+2)
    std::vector<int> cortes;
    cortes.reserve(qtdCortes + 2);
    // garante que começa na segunda posição, não vai mudar o inicio nem o fim
    cortes.push_back(1);
    int posicaoAtual = 1;

    // loop unico -> calcula o tamanho de cada bloco e já monta o corte
    // na mesma iteração, evitando um segundo for separado, era o que eu tava fazendo
    for(int i = 0; i < qtdCortes; i++){
        // começa no maximo de blocos, e depois vai diminuindo
        // são os restantes, logo não precisa contar o qtdCortes+1 que já está na primeira iteração
        int blocosRestantes = qtdCortes - i;

        // aqui é para garantir que todos os blocos tenha o minimo necessario
        // porque vamos supor que cada bloco tenha o minimo de tamanho
        int minimoNecessario = blocosRestantes * tamMin;

        // maior tamanho possível para este bloco
        // esse defini o maximo permitido para seguir o minimo necessario
        // porque ele vai seguir o padrão que todos os blocos precisam ter o minimo necessário
        int maxPermitido = std::min(tamMax, restante - minimoNecessario);

        // aqui foi definido o random com base no que a gente definiu anteriormente
        // para garantir assim que todos os blocos possar ter o minimo

        // esse é o tamanho para aquele bloco em especifico, depois disso diminuimos o valor de restante
        // para continuar podendo fazer o cálculo do maximo permitido
        int tamanhoBloco = Random::getInt(tamMin, maxPermitido);

        restante -= tamanhoBloco;

        // acumula a posição atual com o tamanho do bloco que foi gerado
        // e já registra esse ponto como um corte
        // se for ver o corte vai até o corte + 1 porque o insert é exclusivo no final
        // logo por a gente começar a posição no 1 quando somamos a posição com o tamanho do bloco
        // caimos no ponto que o final é exclusivo e por isso deve ser assim
        posicaoAtual += tamanhoBloco;
        cortes.push_back(posicaoAtual);
    }

    // o último bloco não passa pelo for
    // então o corte é colocado manualmente
    posicaoAtual += restante;
    cortes.push_back(posicaoAtual);

    // foram qtdCortes + 1 dá a quantidade de blocos
    std::vector<int> ordemInsercao(qtdCortes + 1);

    // essa função cria no vetor valores de ordem crescente partindo de 0
    // então é 0, 1, 2, 3... baseado no tamanho definido acima
    std::iota(ordemInsercao.begin(), ordemInsercao.end(), 0);
    // depois de gerar essa ordem, dá um shuffle nela para garantir que vai ser diferente as inserções
    std::shuffle(ordemInsercao.begin(), ordemInsercao.end(), Random::gen());

    std::vector<int> novaRoute;
    // é data.n + 1 porque data.n é só a quantidade na matriz de adj
    // só que o vetor volta para o inicio, então preciso por o (+1)
    novaRoute.reserve(data.n + 1);

    // garante a inserção do começo
    novaRoute.push_back(route[0]);

    int a_somar = 0, a_subtrair = 0;

    // aresta inicial route[0] -> início do bloco 0 que é no indice 1
    // é só cortando o inicio, porque o primeiro valor de cortes[0] = 1
    // foi o primeiro a ser colocado
    a_subtrair += data.matrizAdj[route[0]][route[cortes[0]]];

    // guarda o ultimo nó inserido na novaRoute, para calcular a nova aresta
    // de ligação com o próximo bloco que for inserido
    int noAnterior = route[0];

    for(int b = 0; b < ordemInsercao.size(); b++){
        // SUBTRAIR
        // ele começa, melhor com exemplo
        // cortes[1] que é um indice de corte, porém ele precisa tirar a ligação dele
        // logo ele precisa pegar o indice anterior e cortar com a ligação com ele próprio
        // por isso [b+1] - 1 -> b+1
        a_subtrair += data.matrizAdj[route[cortes[b+1]-1]][route[cortes[b+1]]];

        // SOMAR
        // aqui já temos definido o ponto b, logo ele já começa no indice 0
        // e aqui temos os blocos, onde o b aponta é onde tem os blocos
        // ele defini esse apontamento o inicio e o fim do corte
        // porque ele é um indice
        // exemplo bloco 3 -> indice 3, logo vamos para o corte 3, que é onde ele começa
        // e o seu fim é no corte 4, onde começa o bloco 4
        int indice = ordemInsercao[b];
        int inicio = cortes[indice];
        int fim = cortes[indice + 1];

        // nova aresta -> nó anterior definido lá em cima para termos controle com o primeiro elemento deste bloco
        // que é definido pelo inicio explicado ali em cima
        a_somar += data.matrizAdj[noAnterior][route[inicio]];

        novaRoute.insert(novaRoute.end(), route.begin() + inicio, route.begin() + fim);
        // só um adendo que fui pesquisar, porque isso ia quebrar de alguma forma, porque ia duplicar os valores
        // mas o insert funciona em que, quando chega no route + fim, ele nunca vai até o fim, ele para -1 posição
        // então garante a não duplicação que era meu medo
        // e é isso que inserir o 0 e data.n no vetor de cortes tbm garante que eles estarão no novo vetor
        // é um limite superior não inclusivo -> exclusivo

        // atualiza o nó anterior para o último elemento do bloco que acabou de ser inserido
        // e lembrar que é menos 1, porque o final não é inclusivo no insert
        // logo ele precisa ser incluido no proximo bloco
        noAnterior = route[fim - 1];
    }

    // última aresta somada
    // porque o for para antes inevitavelmente, porque o bloco final é até o fim do data.n
    // que é o ultimo ponto, lembrando que temos que por data.n ainda porque o tamanho do route é data.n + 1
    // aqui precisamos calcular agora o final do bloco para o final do route
    // para poder somar essa ligação
    a_somar += data.matrizAdj[noAnterior][route[data.n]];

    // garante a inserção do fim
    novaRoute.push_back(route[data.n]);
    // novaRoute tamanho = data.n + 1

    int delta = a_somar - a_subtrair;
    cost += delta;

    route = std::move(novaRoute);
}
