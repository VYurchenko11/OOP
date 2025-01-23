#ifndef ICACHEABLE_H
#define ICACHEABLE_H
#include <iostream>

class ICacheable {
public:
    virtual ~ICacheable() = default;
    virtual int get(int key) = 0;
    virtual void put(int key, int value) = 0;
    virtual size_t size() const = 0;
};

#endif 