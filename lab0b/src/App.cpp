#include "App.h"
#include "reader.h"   
#include "spliter.h"  
#include "counter.h"  
#include "writer.h"   
#include <iostream>    

void App::begin(const std::string& inputFile, const std::string& outputFile) {

    Reader reader(inputFile);
    Spliter spliter;
    Counter counter;
    Writer writer;

std::string line;
do {
    line = reader.getLine(); 
    if (line.empty()) {
        break;
    }
    std::list<std::string> words = spliter.Splitword(line); 
    counter.CountWords(words);                     
} while (!line.empty());
    if (!writer.writeCSV(outputFile, counter.SortedWordCount(), counter.TotalWordCount()))
    {
        std::cerr << "Error writing to file\n";     
    }
}