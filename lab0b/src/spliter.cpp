#include "spliter.h"
#include <cctype>
#include <string>

std::list<std::string> Spliter::Splitword(const std::string& line) 
{
    std::list<std::string> words;
    std::string currentWord;
    
    for (auto ch : line) 
    {
        if (std::isalnum((unsigned char)ch)) 
        {
            currentWord.push_back(std::tolower((unsigned char)(ch)));
        } else 
        {
            if (!currentWord.empty()) 
            {
                words.push_back(std::move(currentWord));
                currentWord.clear();  
            }
        }
    }

    if (!currentWord.empty()) 
    {
        words.push_back(std::move(currentWord));
    }

    return words;
}