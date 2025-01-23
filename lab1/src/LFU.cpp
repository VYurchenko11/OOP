#include <iostream>
#include "LFU.h"

LFUcache::LFUcache(int capacity) : capacity(capacity), minFrequency(0) {}

void LFUcache::updateFrequency(int key) {

    int freq = keyFrequency[key];
    freqList[freq].remove(key);

    if (freq == minFrequency && freqList[freq].empty()) {
        minFrequency++;
    }
    
    keyFrequency[key]++;
    freqList[keyFrequency[key]].push_front(key);
}

int LFUcache::get(int key) {
    if (cacheData.find(key) != cacheData.end()) {
        updateFrequency(key);
        return cacheData[key];
    }
    return -1;
}

void LFUcache::put(int key, int value) {
    if (capacity == 0) return; 

    if (cacheData.find(key) != cacheData.end()) {
        cacheData[key] = value;
        updateFrequency(key);
        return;
    }

    if (cacheData.size() >= capacity) {
        int keyToRemove = freqList[minFrequency].back();
        freqList[minFrequency].pop_back();
        cacheData.erase(keyToRemove);
        keyFrequency.erase(keyToRemove);
    }

    cacheData[key] = value;
    keyFrequency[key] = 1; 
    minFrequency = 1; 

    freqList[1].push_front(key);
}

size_t LFUcache::size() const {
    return cacheData.size();
}