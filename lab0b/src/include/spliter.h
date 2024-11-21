#ifndef SPLITER_H
#define SPLITER_H

#include <string>
#include <list> 
#include <cctype> 

class Spliter 
{
    public:
        std::list<std::string> Splitword(const std::string& line); 
};

#endif