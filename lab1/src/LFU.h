#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include "ICacheable.h"

class LFUcache : public ICacheable {
private:
    int capacity;
    int minFrequency;
    std::unordered_map<int, int> cacheData;
    std::unordered_map<int, int> keyFrequency;
    std::unordered_map<int, std::list<int>> freqList;

public:
    void updateFrequency(int key);
    explicit LFUcache(int capacity);
    int get(int key) override;
    void put(int key, int value) override;
    size_t size() const override;
};

#endif