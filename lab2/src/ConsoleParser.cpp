#include <cstring>
#include "ConsoleParser.h"

std::string ConsoleParser::getGameMode() const {
    return gameMode;
}

std::string ConsoleParser::getInputFile() const {
    return inputFile;
}

std::string ConsoleParser::getOutputFile() const {
    return outputFile;
}

int ConsoleParser::getCountOfIterations() const {
    return countOfIterations;
}

void ConsoleParser::parseOptions(int argc, char **argv) {
    try{

        if (argc == 1) {
            this->gameMode = "default";
            return;
        }
        if (argc == 2) {
            this->gameMode = "input file";
            this->inputFile = argv[1];
            return;
        }
        if (argc == 6) {
            this->gameMode = "offline";
            this->inputFile = argv[1];
            for (int i = 2; i < argc; ++i) {
                std::string arg = argv[i];
                if (arg == "--iterations" || arg == "-i") {
                    this->countOfIterations = std::stoi(argv[i + 1]);
                    ++i;
                }else if (arg == "--output" || arg == "-o") {
                    this->outputFile = argv[i + 1];
                    ++i;
                } else {
                    throw std::invalid_argument("Invalid arguments. Correct format: ./GameOfLife <input_file> -i <iterations> -o <output_file>");
                }
            }
        } else {
            throw std::invalid_argument("Invalid number of arguments. Correct format: ./GameOfLife <input_file> -i <iterations> -o <output_file>");
        }

    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        throw;
    }
}
