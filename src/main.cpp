#include "data.h"
#include "localSearch.h"
#include "random.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <instancia> [seed]" << std::endl;
        return 1;
    }

    unsigned int seed = (argc >= 3) ? std::atoi(argv[2]) : static_cast<unsigned int>(time(NULL));
    std::cout << "Seed: " << seed << std::endl;
    Random::randomize(seed);

    Data& data = Data::getInstance();
    data.read(argc, argv);

    Solution s = solve();
    s.print();

    return 0;
}