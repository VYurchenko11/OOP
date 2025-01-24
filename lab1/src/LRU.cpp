#include <iostream>
#include "LRU.h"

LRUcache::LRUcache(int n) : capacity(n) {}

int LRUcache::get(int key) {
    if (cacheMap.find(key) != cacheMap.end()) {
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return cacheList.begin()->second;
    }
    return -1;
}

void LRUcache::put(int key, int value) {
    if (cacheMap.find(key) != cacheMap.end()) {
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheList.begin()->second = value;
        return;
    }
    
    if (cacheMap.find(key) == cacheMap.end()) {
        if (cacheList.size() == capacity) {
            int OldKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(OldKey);
        }
    }
    cacheList.emplace_front(key, value);
    cacheMap[key] = cacheList.begin();
}

size_t LRUcache::size() const {
    return cacheList.size();
}