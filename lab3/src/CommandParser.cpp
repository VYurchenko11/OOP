#include "CommandParser.h"
#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"

bool CommandParser::hasExtension(const std::string& filename, const std::string& extension) const {
    if (filename.size() < extension.size()) return false;
    return filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

void CommandParser::printUsage() {
    std::cout << "Usage: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h                 Show this help message." << std::endl;
    std::cout << "  -c <config.txt>    Path to the configuration file." << std::endl;
    std::cout << "  <output.wav>       Path to the output WAV file." << std::endl;
    std::cout << "  <input.wav>        Path to one or more input WAV files." << std::endl;
}

CommandParser::CommandParser(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("Not enough arguments provided.");
    }

    if (std::string(argv[1]) == "-h") {
        printUsage();
        showHelp = true;
        return;
    }

    if (std::string(argv[1]) != "-c") {
        throw std::invalid_argument("Missing or invalid -c option.");
    }

    if (argc < 5) {
        throw std::invalid_argument("Not enough arguments after -c option.");
    }

    configFile = argv[2];
    outputFile = argv[3];

    if (!hasExtension(configFile, ".txt")) {
        throw FileException("Configuration file must have a .txt extension.");
    }

    if (!hasExtension(outputFile, ".wav")) {
        throw FileException("Output file must have a .wav extension.");
    }

    for (int i = 4; i < argc; ++i) {
        if (hasExtension(argv[i], ".wav")) {
            inputFiles.push_back(argv[i]);
        } else {
            throw FileException(std::string("Invalid file extension for input file: ") + argv[i]);
        }
    }

    if (inputFiles.empty()) {
        throw FileException("No valid input .wav files provided.");
    }
}

bool CommandParser::parse() const {
    return !showHelp;
}

std::string CommandParser::getConfigFile() const {
    return configFile;
}

std::string CommandParser::getOutputFile() const {
    return outputFile;
}

std::vector<std::string> CommandParser::getInputFiles() const {
    return inputFiles;
}
