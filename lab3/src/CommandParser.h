#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"

class CommandParser {
private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    bool showHelp = false;

    bool hasExtension(const std::string& filename, const std::string& extension) const;

public:
    static void printUsage();

    CommandParser(int argc, char* argv[]);

    bool parse() const;

    std::string getConfigFile() const;

    std::string getOutputFile() const;

    std::vector<std::string> getInputFiles() const;
};

#endif
