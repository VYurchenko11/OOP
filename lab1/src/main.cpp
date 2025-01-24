#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>
#include "LRU.h"
#include "LFU.h"
#include "CounterFibonachi.h"

int main(int argc, char* argv[]) {

    try {
        if (argc != 2) {
            throw std::runtime_error("Error: invalid number of arguments");
        }

        int n = std::stoi(argv[1]);
        if (n < 0) {
            throw std::invalid_argument("Error: Fibonacci index cannot be negative");
        }

        LRUcache LRUCache(10);
        LFUcache LFUCache(10);
        CounterFibonachi counterfibonachi;

        int LRUFibonachi = counterfibonachi.counterfibonachi(n, LRUCache);
        std::cout << "LRU Cache Fibonacci(" << n << ") = " << LRUFibonachi << std::endl;

        int LFUFibonachi = counterfibonachi.counterfibonachi(n, LFUCache);
        std::cout << "LFU Cache Fibonacci(" << n << ") = " << LFUFibonachi << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}