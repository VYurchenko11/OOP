#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include "Exceptions.h"

ConfigParser::ConfigParser(const std::string &filename) : filename(filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        throw FileException("ConfigParser: Unable to open the configuration file: " + filename);
    }

    for (std::string line; std::getline(file, line); ) {
        if (!line.empty()) { // Сохраняем только непустые строки
            lines.emplace_back(line);
        }
    }

    if (lines.empty()) {
        throw FileException("ConfigParser: Configuration file is empty: " + filename);
    }
}

std::vector<std::string> ConfigParser::parseLine(const int& lineIndex) const {
    if (lineIndex < 0 || static_cast<size_t>(lineIndex) >= lines.size()) {
        throw std::out_of_range("ConfigParser: Line index " + std::to_string(lineIndex) + " is out of range");
    }

    std::vector<std::string> args;
    std::istringstream stream(lines[lineIndex]);
    std::string arg;

    while (stream >> arg) {
        args.push_back(arg);
    }

    return args;
}

size_t ConfigParser::getLinesCount() const {
    return lines.size();
}