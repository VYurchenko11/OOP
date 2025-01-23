#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include "ICacheable.h"

class LRUcache : public ICacheable {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList;
    std::unordered_map<int, std::list<std::pair<int,int>> :: iterator> cacheMap;
public:
    explicit LRUcache(int n);
    int get (int key) override;
    void put (int key, int value) override;
    size_t size() const override;
};

#endif
