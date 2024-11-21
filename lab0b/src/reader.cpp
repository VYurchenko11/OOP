#include "reader.h"

Reader::Reader(const std::string& nameFile) {
    inputFile.open(nameFile);
}

std::string Reader::getLine() 
{
    if (!inputFile.is_open()) 
    {
        return "";  
    }
    std::string line;
    if (std::getline(inputFile, line)) 
    {
        return line; 
    } else 
    {
        return "";
    }
}

void Reader::close() 
{
    if (inputFile.is_open()) 
    {
        inputFile.close();
    }
}

Reader::~Reader() 
{
    close();
}