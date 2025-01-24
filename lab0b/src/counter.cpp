#include "counter.h"
#include <algorithm>


void Counter::CountWords(std::list<std::string>& inputWords) 
{
    for (const auto& word : inputWords) 
    {
        if (!word.empty()) 
        { 
            countMap[word]++;
            totalWords++; 
        }
    }
}

int Counter::TotalWordCount() const 
{
    return totalWords;
}

std::vector<std::pair<std::string, int>> Counter::SortedWordCount() const 
{
    std::vector<std::pair<std::string, int>> sortedCounts(countMap.begin(), countMap.end());

    std::sort(sortedCounts.begin(), sortedCounts.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) 
    {
        return a.second > b.second;
    });

    return sortedCounts;
}