#ifndef CONSOLEPARSER_H
#define CONSOLEPARSER_H

#include <iostream>
#include "Life.h"

class ConsoleParser {
private:
    std::string gameMode;
    std::string inputFile;
    std::string outputFile;
    int countOfIterations = 0;
public:
    ConsoleParser() = default;

    std::string getGameMode() const;
    std::string getInputFile() const;
    std::string getOutputFile() const;

    int getCountOfIterations() const;

    void parseOptions(int argc, char **argv);
};

#endif
