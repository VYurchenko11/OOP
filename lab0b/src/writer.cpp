#include "writer.h"
#include <fstream>
#include <iostream>

bool Writer::writeCSV(const std::string& fileName, const std::vector<std::pair<std::string, int>>& sortedWords, int totalWords) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) 
    {
        std::cerr << "Unable to open file for writing.\n";
        return false;  
    }

    outputFile << "Word Frequency Frequency(%)\n";

    for (const auto& entry : sortedWords) 
    {
        double frequencyPercentage = (entry.second / static_cast<double>(totalWords)) * 100;

        outputFile << entry.first << "\t" << entry.second << "\t" << frequencyPercentage << "%\n";
    }

    outputFile.close();
    return true;
}
