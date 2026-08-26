#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "solution.h"
#include <iostream>

void RVND(Solution &s);

bool bestImprovementSwap(Solution &s);
bool bestImprovmentOrOpt2(Solution &s);
bool bestImprovmentReinsertion(Solution &s);
bool bestImprovmentOrOpt3(Solution &s);
bool bestImprovmentOpt2(Solution &s);


Solution solve();

#endif // LOCAL_SEARCH_H