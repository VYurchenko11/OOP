#ifndef COUNTER_H
#define COUNTER_H

#include <map> 
#include <list>
#include <string>
#include <vector> 

class Counter 
{
private:
    std::map<std::string, int> countMap;
public:
    int totalWords = 0; 
    void CountWords(std::list<std::string>& inputWords); 
    int TotalWordCount() const; 
    std::vector<std::pair<std::string, int>> SortedWordCount() const;  
};

#endif