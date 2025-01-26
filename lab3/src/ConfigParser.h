#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <vector>

class ConfigParser {
private:
    std::string filename;
    std::vector<std::string> lines;
public:
    explicit ConfigParser(const std::string& filename);
    std::vector<std::string> parseLine(const int& lineIndex) const;
    size_t getLinesCount() const;
};

#endif