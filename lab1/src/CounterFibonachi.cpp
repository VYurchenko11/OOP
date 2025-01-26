#include <iostream>
#include "LRU.h"
#include "LFU.h"
#include "CounterFibonachi.h"

int CounterFibonachi::counterfibonachi(int n, ICacheable& cache) {
    if (n < 0) {
        throw std::invalid_argument("Fibonacci index cannot be negative");
    }

    if (n == 0) return 0;
    if (n == 1) return 1;

    int cachedResult = cache.get(n);
    if (cachedResult != -1) {
        return cachedResult;
    }
    
    int result = counterfibonachi(n - 1, cache) + counterfibonachi(n - 2, cache);

    cache.put(n, result);

    return result;
}