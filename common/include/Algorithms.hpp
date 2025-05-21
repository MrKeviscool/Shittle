#pragma once

#include <vector>

//time-comlexity: O(n log (log n))
std::vector<int> getPrimes(const int to);

//time-complexity: O(log(min(a, b)))
unsigned int getGcf(const unsigned int a, const unsigned int b);